/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef _DISP_INCLUDE_H_
#define _DISP_INCLUDE_H_

#include <typedef.h>
#include <stdbool.h>
#include <hal_sem.h>
#include <hal_clk.h>
#include <log.h>
#include <aw_list.h>
#include <hal_sem.h>
#include <hal_gpio.h>
#include <sunxi_hal_pwm.h>
#include <hal_atomic.h>
#include <workqueue.h>
#include <video/sunxi_display2.h>
#include <video/sunxi_metadata.h>
#include "../disp_sys_intf.h"
#include <hal_mem.h>
#include <hal_queue.h>
#include <hal_log.h>
#include "disp_features.h"




#define DISP2_DEBUG_LEVEL 1

#if DISP2_DEBUG_LEVEL == 1
#define DE_INF(fmt, ...)        do {hal_log_info("disp:[%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__);} while (0)
#define DE_MSG(fmt, ...)        do {hal_log_info("disp:[%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__);} while (0)
#define DE_HERE
#define DE_DBG(fmt, ...)      do {hal_log_debug("disp:[%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__);} while (0)
#elif DISP2_DEBUG_LEVEL == 2
#define DE_INF(...)  hal_log_info(__VA_ARGS__)
#define DE_HERE(...) hal_log_info(__VA_ARGS__)
#define DE_DBG(...)  hal_log_debug(__VA_ARGS__)
#else
#define DE_INF(msg...) asm("nop")
#define DE_MSG(msg...) asm("nop")
#define DE_HERE asm("nop")
#define DE_DBG(msg...) asm("nop")
#endif

#define DE_WRN(fmt, ...) do {hal_log_warn("disp:[%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__);} while (0)

#define DISP_PRINT printf

#define DISP_IRQ_RETURN DIS_SUCCESS


#define DEFAULT_PRINT_LEVLE 0
#if defined(CONFIG_FPGA_V4_PLATFORM) \
    || defined(CONFIG_FPGA_V7_PLATFORM) \
    || defined(CONFIG_A67_FPGA)
#define __FPGA_DEBUG__
#endif

#define SETMASK(width, shift)   ((width?((-1U) >> (32-width)):0)  << (shift))
#define CLRMASK(width, shift)   (~(SETMASK(width, shift)))
#define GET_BITS(shift, width, reg)     \
    (((reg) & SETMASK(width, shift)) >> (shift))
#define SET_BITS(shift, width, reg, val) \
    (((reg) & CLRMASK(width, shift)) | (val << (shift)))

#define DISPALIGN(value, align) ((align == 0) ? \
                value : \
                (((value) + ((align) - 1)) & ~((align) - 1)))

#ifndef abs
#define abs(x) (((x)&0x80000000) ? (0-(x)):(x))
#endif

#define LCD_GAMMA_TABLE_SIZE (256 * sizeof(unsigned int))

#define ONE_SEC 1000000000ull

#undef readl
#define readl(addr)     (*((volatile unsigned int  *)(addr)))
#undef writel
#define writel(v, addr) (*((volatile unsigned int  *)(addr)) = (unsigned int)(v))


typedef hal_clk_id_t disp_clk_t;

struct panel_extend_para {
    u32 lcd_gamma_en;
    u32 lcd_gamma_tbl[256];
    u32 lcd_cmap_en;
    u32 lcd_cmap_tbl[2][3][4];
    u32 lcd_bright_curve_tbl[256];
};

enum disp_return_value {
    DIS_SUCCESS = 0,
    DIS_FAIL = -1,
    DIS_PARA_FAILED = -2,
    DIS_PRIO_ERROR = -3,
    DIS_OBJ_NOT_INITED = -4,
    DIS_NOT_SUPPORT = -5,
    DIS_NO_RES = -6,
    DIS_OBJ_COLLISION = -7,
    DIS_DEV_NOT_INITED = -8,
    DIS_DEV_SRAM_COLLISION = -9,
    DIS_TASK_ERROR = -10,
    DIS_PRIO_COLLSION = -11
};

/*basic data information definition*/
enum disp_layer_feat {
    DISP_LAYER_FEAT_GLOBAL_ALPHA = 1 << 0,
    DISP_LAYER_FEAT_PIXEL_ALPHA = 1 << 1,
    DISP_LAYER_FEAT_GLOBAL_PIXEL_ALPHA = 1 << 2,
    DISP_LAYER_FEAT_PRE_MULT_ALPHA = 1 << 3,
    DISP_LAYER_FEAT_COLOR_KEY = 1 << 4,
    DISP_LAYER_FEAT_ZORDER = 1 << 5,
    DISP_LAYER_FEAT_POS = 1 << 6,
    DISP_LAYER_FEAT_3D = 1 << 7,
    DISP_LAYER_FEAT_SCALE = 1 << 8,
    DISP_LAYER_FEAT_DE_INTERLACE = 1 << 9,
    DISP_LAYER_FEAT_COLOR_ENHANCE = 1 << 10,
    DISP_LAYER_FEAT_DETAIL_ENHANCE = 1 << 11,
};

enum disp_pixel_type {
    DISP_PIXEL_TYPE_RGB = 0x0,
    DISP_PIXEL_TYPE_YUV = 0x1,
};

enum disp_layer_dirty_flags {
    LAYER_ATTR_DIRTY = 0x00000001,
    LAYER_VI_FC_DIRTY = 0x00000002,
    LAYER_HADDR_DIRTY = 0x00000004,
    LAYER_SIZE_DIRTY = 0x00000008,
    BLEND_ENABLE_DIRTY = 0x00000010,
    BLEND_ATTR_DIRTY = 0x00000020,
    BLEND_CTL_DIRTY        = 0x00000040,
    BLEND_OUT_DIRTY        = 0x00000080,
    LAYER_ATW_DIRTY        = 0x00000100,
    LAYER_HDR_DIRTY        = 0x00000200,
    LAYER_ALL_DIRTY        = 0x000003ff,
};

enum disp_manager_dirty_flags {
    MANAGER_ENABLE_DIRTY = 0x00000001,
    MANAGER_CK_DIRTY = 0x00000002,
    MANAGER_BACK_COLOR_DIRTY = 0x00000004,
    MANAGER_SIZE_DIRTY = 0x00000008,
    MANAGER_COLOR_RANGE_DIRTY = 0x00000010,
    MANAGER_COLOR_SPACE_DIRTY = 0x00000020,
    MANAGER_BLANK_DIRTY = 0x00000040,
    MANAGER_KSC_DIRTY = 0x00000080,
    MANAGER_PALETTE_DIRTY = 0x00000100,
    MANAGER_ALL_DIRTY = 0x00000fff,
};

/* disp_atw_info_inner - asynchronous time wrap infomation
 *
 * @used: indicate if the atw funtion is used
 * @mode: atw mode
 * @b_row: the row number of the micro block
 * @b_col: the column number of the micro block
 * @cof_fd: dma_buf fd for the buffer contaied coefficient for atw
 */
struct disp_atw_info_inner {
    bool used;
    enum disp_atw_mode mode;
    unsigned int b_row;
    unsigned int b_col;
    int cof_fd;
    unsigned long long cof_addr;
};

/* disp_fb_info_inner - image buffer info on the inside
 *
 * @addr: buffer address for each plane
 * @size: size<width,height> for each buffer, unit:pixels
 * @align: align for each buffer, unit:bytes
 * @format: pixel format
 * @color_space: color space
 * @trd_right_addr: the right-eye buffer address for each plane,
 *                  valid when frame-packing 3d buffer input
 * @pre_multiply: indicate the pixel use premultiplied alpha
 * @crop: crop rectangle for buffer to be display
 * @flag: indicate stereo/non-stereo buffer
 * @scan: indicate interleave/progressive scan type, and the scan order
 * @metadata_buf: the phy_address to the buffer contained metadata for fbc/hdr
 * @metadata_size: the size of metadata buffer, unit:bytes
 * @metadata_flag: the flag to indicate the type of metadata buffer
 *  0     : no metadata
 *  1 << 0: hdr static metadata
 *  1 << 1: hdr dynamic metadata
 *  1 << 4: frame buffer compress(fbc) metadata
 *  x     : all type could be "or" together
 */
struct disp_fb_info_inner {
    int fd;
    struct dma_buf           *dmabuf;
    unsigned long long       addr[3];
    struct disp_rectsz       size[3];
    unsigned int             align[3];
    enum disp_pixel_format   format;
    enum disp_color_space    color_space;
    int                      trd_right_fd;
    unsigned int             trd_right_addr[3];
    bool                     pre_multiply;
    struct disp_rect64       crop;
    enum disp_buffer_flags   flags;
    enum disp_scan_flags     scan;
    enum disp_eotf           eotf;
    int                      depth;
    unsigned int             fbd_en;
    unsigned int             lbc_en;
    int                      metadata_fd;
    unsigned long long       metadata_buf;
    unsigned int             metadata_size;
    unsigned int             metadata_flag;
    struct disp_lbc_info     lbc_info;
};

/* disp_layer_info_inner - layer info on the inside
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
struct disp_layer_info_inner {
    enum disp_layer_mode      mode;
    unsigned char             zorder;
    unsigned char             alpha_mode;
    unsigned char             alpha_value;
    struct disp_rect          screen_win;
    bool                      b_trd_out;
    enum disp_3d_out_mode     out_trd_mode;
    union {
        unsigned int               color;
        struct disp_fb_info_inner  fb;
    };

    unsigned int              id;
    struct disp_atw_info_inner atw;
};

/* disp_layer_config_inner - layer config on the inside
 *
 * @info: layer info
 * @enable: indicate to enable/disable the layer
 * @channel: the channel index of the layer, 0~max-channel-number
 * @layer_id: the layer index of the layer widthin it's channel
 */
struct disp_layer_config_inner {
    struct disp_layer_info_inner info;
    bool enable;
    unsigned int channel;
    unsigned int layer_id;
};

/* disp_layer_config_ops - operations for layer config
 *
 * @vmap:vmap a block contigous phys memory into virtual space
 * @vunmap: release virtual mapping obtained by vmap()
 */
struct disp_layer_config_ops {
    void *(*vmap)(unsigned long phys_addr, unsigned long size);
    void (*vunmap)(const void *vaddr);
};
struct disp_layer_config_data {
    struct disp_layer_config_inner config;
    enum disp_layer_dirty_flags flag;
    struct disp_layer_config_ops ops;
};

struct disp_manager_info {
    struct disp_color back_color;
    struct disp_colorkey ck;
    struct disp_rect size;
    enum disp_csc_type cs;
    enum disp_color_space color_space;
    u32 color_range;
    u32 interlace;
    bool enable;
    /* index of device */
    u32 disp_device;
    /* indicate the index of timing controller */
    u32 hwdev_index;
    /* true: disable all layer; false: enable layer if requested */
    bool blank;
    u32 de_freq;
    enum disp_eotf eotf; /* sdr/hdr10/hlg */
    enum disp_data_bits data_bits;
    struct disp_palette_config palette;
};

struct disp_manager_data {
    struct disp_manager_info config;
    enum disp_manager_dirty_flags flag;
};

struct disp_clk_info {
    u32 clk;
    u32 clk_div;
    u32 h_clk;
    u32 clk_src;
    u32 clk_div2;

    u32 clk_p;
    u32 clk_div_p;
    u32 h_clk_p;
    u32 clk_src_p;

    u32 ahb_clk;
    u32 h_ahb_clk;
    u32 dram_clk;
    u32 h_dram_clk;

    bool enabled;
};

struct disp_enhance_info {
    /* basic adjust */
    /*
     * enhance parameters : 0~10, bigger value, stronger enhance level
     * mode : combination of enhance_mode and dev_type
     * enhance_mode : bit31~bit16 of mode
     *              : 0-disable; 1-enable; 2-demo(enable half window)
     * dev_type : bit15~bit0 of mode
     *          : 0-lcd; 1-tv(hdmi, cvbs, vga, ypbpr)
     */
    u32 bright;
    u32 contrast;
    u32 saturation;
    u32 hue;
    u32         edge;
    u32         detail;
    u32         denoise;
    u32 mode;
    /* ehnance */
    u32 sharp;      /* 0-off; 1~3-on. */
    u32 auto_contrast;  /* 0-off; 1~3-on. */
    u32 auto_color;     /* 0-off; 1-on. */
    u32 fancycolor_red; /* 0-Off; 1-2-on. */
    u32 fancycolor_green;   /* 0-Off; 1-2-on. */
    u32 fancycolor_blue;    /* 0-Off; 1-2-on. */
    struct disp_rect window;
    u32 enable;
    struct disp_rect size;
    u32 demo_enable;    /* 1: enable demo mode */
};

enum disp_enhance_dirty_flags {
    ENH_NONE_DIRTY       = 0x0,
    ENH_ENABLE_DIRTY     = 0x1 << 0,  /* enable dirty */
    ENH_SIZE_DIRTY       = 0x1 << 1,  /* size dirty */
    ENH_FORMAT_DIRTY     = 0x1 << 2,  /* overlay format dirty */
    ENH_BYPASS_DIRTY     = 0x1 << 3, /* bypass dirty */
    ENH_INIT_DIRTY       = 0x1 << 8,  /* initial parameters dirty */
    ENH_MODE_DIRTY       = 0X1 << 9,  /* enhance mode dirty */
    ENH_BRIGHT_DIRTY     = 0x1 << 10,  /* brightness level dirty */
    ENH_CONTRAST_DIRTY   = 0x1 << 11,  /* contrast level dirty */
    ENH_EDGE_DIRTY       = 0x1 << 12,  /* edge level dirty */
    ENH_DETAIL_DIRTY     = 0x1 << 13,  /* detail level dirty */
    ENH_SAT_DIRTY        = 0x1 << 14,  /* saturation level dirty */
    ENH_DNS_DIRTY        = 0x1 << 15, /* de-noise level dirty */
    ENH_USER_DIRTY       = 0xff00,     /* dirty by user */
    ENH_ALL_DIRTY        = 0xffff      /* all dirty */

};

struct disp_enhance_config {
    struct disp_enhance_info info;
    enum disp_enhance_dirty_flags flags;
};

enum disp_smbl_dirty_flags {
    SMBL_DIRTY_NONE = 0x00000000,
    SMBL_DIRTY_ENABLE = 0x00000001,
    SMBL_DIRTY_WINDOW = 0x00000002,
    SMBL_DIRTY_SIZE = 0x00000004,
    SMBL_DIRTY_BL = 0x00000008,
    SMBL_DIRTY_ALL = 0x0000000F,
};

struct disp_smbl_info {
    struct disp_rect window;
    u32 enable;
    struct disp_rect size;
    u32 backlight;
    u32 backlight_dimming;
    enum disp_smbl_dirty_flags flags;
};

struct disp_csc_config {
    u32 in_fmt;
    u32 in_mode;
    u32 in_color_range;
    u32 out_fmt;
    u32 out_mode;
    u32 out_color_range;
    u32 brightness;
    u32 contrast;
    u32 saturation;
    u32 hue;
    u32 enhance_mode;
    u32 color;
    u32 in_eotf;
    u32 out_eotf;
};

enum {
    DE_RGB = 0,
    DE_YUV = 1,
};

enum disp_capture_dirty_flags {
    CAPTURE_DIRTY_ADDRESS = 0x00000001,
    CAPTURE_DIRTY_WINDOW = 0x00000002,
    CAPTURE_DIRTY_SIZE = 0x00000004,
    CAPTURE_DIRTY_ALL = 0x00000007,
};
/* disp_s_frame_inner - display simple frame buffer
 *
 * @format: pixel format of fb
 * @size: size for each plane
 * @crop: crop zone to be fill image data
 * @fd: dma_buf fd
 * @addr: buffer addr for each plane
 */
struct disp_s_frame_inner {
    enum disp_pixel_format format;
    struct disp_rectsz size[3];
    struct disp_rect crop;
    unsigned long long addr[3];
    int fd;
};

/* disp_capture_info_inner - display capture information
 *
 * @window: the rectange on the screen to be capture
 * @out_frame: the framebuffer to be restore capture image data
 */
struct disp_capture_info_inner {
    struct disp_rect window;
    struct disp_s_frame_inner out_frame;
};
/* disp_capture_config - configuration for capture function
 *
 * @in_frame: input frame information
 * @out_frame: output framebuffer infomation
 * @disp: indicate which disp channel to be capture
 * @flags: caputre flags
 */
struct disp_capture_config {
    struct disp_s_frame in_frame;   /* only format/size/crop valid */
    struct disp_s_frame out_frame;
    u32 disp;       /* which disp channel to be capture */
    enum disp_capture_dirty_flags flags;
};

enum disp_lcd_if {
    LCD_IF_HV = 0,
    LCD_IF_CPU = 1,
    LCD_IF_LVDS = 3,
    LCD_IF_DSI = 4,
    LCD_IF_EDP = 5,
    LCD_IF_EXT_DSI = 6,
    LCD_IF_VDPO = 7,
};

enum disp_lcd_hv_if {
    LCD_HV_IF_PRGB_1CYC = 0,    /* parallel hv */
    LCD_HV_IF_SRGB_3CYC = 8,    /* serial hv */
    LCD_HV_IF_DRGB_4CYC = 10,   /* Dummy RGB */
    LCD_HV_IF_RGBD_4CYC = 11,   /* RGB Dummy */
    LCD_HV_IF_CCIR656_2CYC = 12,
};

enum disp_lcd_hv_srgb_seq {
    LCD_HV_SRGB_SEQ_RGB_RGB = 0,
    LCD_HV_SRGB_SEQ_RGB_BRG = 1,
    LCD_HV_SRGB_SEQ_RGB_GBR = 2,
    LCD_HV_SRGB_SEQ_BRG_RGB = 4,
    LCD_HV_SRGB_SEQ_BRG_BRG = 5,
    LCD_HV_SRGB_SEQ_BRG_GBR = 6,
    LCD_HV_SRGB_SEQ_GRB_RGB = 8,
    LCD_HV_SRGB_SEQ_GRB_BRG = 9,
    LCD_HV_SRGB_SEQ_GRB_GBR = 10,
};

enum disp_lcd_hv_syuv_seq {
    LCD_HV_SYUV_SEQ_YUYV = 0,
    LCD_HV_SYUV_SEQ_YVYU = 1,
    LCD_HV_SYUV_SEQ_UYUV = 2,
    LCD_HV_SYUV_SEQ_VYUY = 3,
};

enum disp_lcd_hv_syuv_fdly {
    LCD_HV_SYUV_FDLY_0LINE = 0,
    LCD_HV_SRGB_FDLY_2LINE = 1, /* ccir ntsc */
    LCD_HV_SRGB_FDLY_3LINE = 2, /* ccir pal */
};

enum disp_lcd_cpu_if {
    LCD_CPU_IF_RGB666_18PIN = 0,
    LCD_CPU_IF_RGB666_9PIN = 10,
    LCD_CPU_IF_RGB666_6PIN = 12,
    LCD_CPU_IF_RGB565_16PIN = 8,
    LCD_CPU_IF_RGB565_8PIN = 14,
};

enum disp_lcd_cpu_mode {
    LCD_CPU_AUTO_MODE = 0,
    LCD_CPU_TRIGGER_MODE = 1,
};

enum disp_lcd_te {
    LCD_TE_DISABLE = 0,
    LCD_TE_RISING = 1,
    LCD_TE_FALLING = 2,
};

enum disp_lcd_lvds_if {
    LCD_LVDS_IF_SINGLE_LINK = 0,
    LCD_LVDS_IF_DUAL_LINK = 1,
    LCD_LVDS_IF_DUAL_LINK_SAME_SRC = 2,
};

enum disp_lcd_lvds_colordepth {
    LCD_LVDS_8bit = 0,
    LCD_LVDS_6bit = 1,
};

enum disp_lcd_lvds_mode {
    LCD_LVDS_MODE_NS = 0,
    LCD_LVDS_MODE_JEIDA = 1,
};

enum disp_lcd_dsi_if {
    LCD_DSI_IF_VIDEO_MODE = 0,
    LCD_DSI_IF_COMMAND_MODE = 1,
    LCD_DSI_IF_BURST_MODE = 2,
};

enum disp_lcd_dsi_lane {
    LCD_DSI_1LANE = 1,
    LCD_DSI_2LANE = 2,
    LCD_DSI_3LANE = 3,
    LCD_DSI_4LANE = 4,
};

enum disp_lcd_dsi_format {
    LCD_DSI_FORMAT_RGB888 = 0,
    LCD_DSI_FORMAT_RGB666 = 1,
    LCD_DSI_FORMAT_RGB666P = 2,
    LCD_DSI_FORMAT_RGB565 = 3,
};

enum disp_lcd_frm {
    LCD_FRM_BYPASS = 0,
    LCD_FRM_RGB666 = 1,
    LCD_FRM_RGB565 = 2,
};

enum disp_lcd_cmap_color {
    LCD_CMAP_B0 = 0x0,
    LCD_CMAP_G0 = 0x1,
    LCD_CMAP_R0 = 0x2,
    LCD_CMAP_B1 = 0x4,
    LCD_CMAP_G1 = 0x5,
    LCD_CMAP_R1 = 0x6,
    LCD_CMAP_B2 = 0x8,
    LCD_CMAP_G2 = 0x9,
    LCD_CMAP_R2 = 0xa,
    LCD_CMAP_B3 = 0xc,
    LCD_CMAP_G3 = 0xd,
    LCD_CMAP_R3 = 0xe,
};

struct __disp_dsi_dphy_timing_t {
    unsigned int lp_clk_div;
    unsigned int hs_prepare;
    unsigned int hs_trail;
    unsigned int clk_prepare;
    unsigned int clk_zero;
    unsigned int clk_pre;
    unsigned int clk_post;
    unsigned int clk_trail;
    unsigned int hs_dly_mode;
    unsigned int hs_dly;
    unsigned int lptx_ulps_exit;
    unsigned int hstx_ana0;
    unsigned int hstx_ana1;
};

/**
 * lcd tcon mode(dual tcon drive dual dsi)
 */
enum disp_lcd_tcon_mode {
    DISP_TCON_NORMAL_MODE = 0,
    DISP_TCON_MASTER_SYNC_AT_FIRST_TIME,
    DISP_TCON_MASTER_SYNC_EVERY_FRAME,
    DISP_TCON_SLAVE_MODE,
    DISP_TCON_DUAL_DSI,
};

enum disp_lcd_dsi_port {
    DISP_LCD_DSI_SINGLE_PORT = 0,
    DISP_LCD_DSI_DUAL_PORT,
};

struct disp_lcd_esd_info {
    /*1:reset all module include tcon; 0:reset panel only*/
    unsigned char level;
    /*unit:frame*/
    unsigned short freq;
    /*1:in disp isr; 0:in reflush work*/
    unsigned char esd_check_func_pos;
    /*count*/
    unsigned int cnt;
    /*reset count*/
    unsigned int rst_cnt;
};

struct disp_panel_para {
    enum disp_lcd_if lcd_if;

    enum disp_lcd_hv_if lcd_hv_if;
    enum disp_lcd_hv_srgb_seq lcd_hv_srgb_seq;
    enum disp_lcd_hv_syuv_seq lcd_hv_syuv_seq;
    enum disp_lcd_hv_syuv_fdly lcd_hv_syuv_fdly;

    enum disp_lcd_lvds_if lcd_lvds_if;
    enum disp_lcd_lvds_colordepth lcd_lvds_colordepth;
    enum disp_lcd_lvds_mode lcd_lvds_mode;
    unsigned int lcd_lvds_io_polarity;

    enum disp_lcd_cpu_if lcd_cpu_if;
    enum disp_lcd_te lcd_cpu_te;
    enum disp_lcd_dsi_port lcd_dsi_port_num;
    enum disp_lcd_tcon_mode  lcd_tcon_mode;
    unsigned int             lcd_slave_stop_pos;
    unsigned int             lcd_sync_pixel_num;
    unsigned int             lcd_sync_line_num;
    unsigned int             lcd_slave_tcon_num;
    enum disp_lcd_cpu_mode lcd_cpu_mode;

    enum disp_lcd_dsi_if lcd_dsi_if;
    enum disp_lcd_dsi_lane lcd_dsi_lane;
    enum disp_lcd_dsi_format lcd_dsi_format;
    unsigned int lcd_dsi_eotp;
    unsigned int lcd_dsi_vc;
    enum disp_lcd_te lcd_dsi_te;

    unsigned int             lcd_tcon_en_odd_even;

    unsigned int lcd_dsi_dphy_timing_en;
    struct __disp_dsi_dphy_timing_t *lcd_dsi_dphy_timing_p;

    unsigned int lcd_fsync_en;
    unsigned int lcd_fsync_act_time;
    unsigned int lcd_fsync_dis_time;
    unsigned int lcd_fsync_pol;

    unsigned int lcd_dclk_freq;
    unsigned int lcd_x; /* horizontal resolution */
    unsigned int lcd_y; /* vertical resolution */
    unsigned int lcd_width; /* width of lcd in mm */
    unsigned int lcd_height;    /* height of lcd in mm */
    unsigned int lcd_xtal_freq;

    unsigned int lcd_pwm_used;
    unsigned int lcd_pwm_ch;
    unsigned int lcd_pwm_freq;
    unsigned int lcd_pwm_pol;

    unsigned int lcd_rb_swap;
    unsigned int lcd_rgb_endian;

    unsigned int lcd_vt;
    unsigned int lcd_ht;
    unsigned int lcd_vbp;
    unsigned int lcd_hbp;
    unsigned int lcd_vspw;
    unsigned int lcd_hspw;

    unsigned int lcd_interlace;
    unsigned int lcd_hv_clk_phase;
    unsigned int lcd_hv_sync_polarity;
    unsigned int lcd_de_polarity;

    unsigned int lcd_frm;
    unsigned int lcd_gamma_en;
    unsigned int lcd_cmap_en;
    unsigned int lcd_bright_curve_en;

    char lcd_size[8];   /* e.g. 7.9, 9.7 */
    char lcd_model_name[32];
    char lcd_driver_name[32];

    unsigned int tcon_index;    /* not need to config for user */
    unsigned int lcd_fresh_mode;    /* not need to config for user */
    unsigned int lcd_dclk_freq_original;/* not need to config for user */
    unsigned int ccir_clk_div;/*not need to config for user*/
    unsigned int input_csc;/*not need to config for user*/
    unsigned int lcd_gsensor_detect;
    unsigned int lcd_hv_data_polarity;

};

enum disp_mod_id {
    DISP_MOD_DE = 0,
#if defined(CONFIG_ARCH_SUN50IW10)
    DISP_MOD_DE1,
#endif
    DISP_MOD_DEVICE,    /* for timing controller common module */
#if defined(CONFIG_ARCH_SUN50IW10)
    DISP_MOD_DEVICE1,
#endif
    DISP_MOD_LCD0,
    DISP_MOD_LCD1,
    DISP_MOD_LCD2,
    DISP_MOD_LCD3,
    DISP_MOD_DSI0,
    DISP_MOD_DSI1,
    DISP_MOD_DSI2,
    DISP_MOD_DSI3,
    DISP_MOD_HDMI,
    DISP_MOD_LVDS,
    DISP_MOD_EINK,
    DISP_MOD_EDMA,
    DISP_MOD_VDPO,
#if defined(CONFIG_ARCH_SUN50IW10)
    DISP_MOD_DPSS0,
    DISP_MOD_DPSS1,
#endif
    DISP_MOD_NUM,
};

typedef enum {
    DISP_NOT_UPDATE = 0,
    DISP_NORMAL_UPDATE = 1,
    DISP_SMOOTH_UPDATE = 2,
} disp_config_update_t;


struct disp_bootloader_info {
    int sync;       /* 1: sync width bootloader */
    int disp;       /* output disp at bootloader period */
    int type;       /* output type at bootloader period */
    int mode; /* output mode at bootloader period */
    int format;/* YUV or RGB */
    int bits; /* color deep */
    int eotf;
    int cs; /* color space */
    enum disp_dvi_hdmi  dvi_hdmi;
    enum disp_color_range   range;
    enum disp_scan_info     scan;
    unsigned int            aspect_ratio;

};

#define DEBUG_TIME_SIZE 100
struct disp_health_info {
    unsigned long sync_time[DEBUG_TIME_SIZE];   /* for_debug */
    unsigned int sync_time_index;   /* for_debug */
    unsigned int skip_cnt;
    unsigned int          skip_cnt_timeout;
    unsigned int error_cnt; /* under flow .ect */
    unsigned long long    irq_cnt;
    unsigned int vsync_cnt;
    unsigned int          vsync_skip_cnt;
};

struct disp_bsp_init_para {
    uintptr_t reg_base[DISP_MOD_NUM];
    u32 irq_no[DISP_MOD_NUM];
    disp_clk_t clk_de[DE_NUM];
    disp_clk_t clk_bus_de[DE_NUM];
    disp_clk_t clk_bus_dpss_top[DISP_DEVICE_NUM];
    disp_clk_t clk_tcon_lcd[DISP_DEVICE_NUM];
    disp_clk_t clk_bus_tcon_lcd[DISP_DEVICE_NUM];
    disp_clk_t clk_mipi_dsi[CLK_DSI_NUM];
    disp_clk_t clk_bus_mipi_dsi[CLK_DSI_NUM];
    struct reset_control *rst_bus_lvds;
    s32 (*disp_int_process)(u32 sel);
    s32 (*vsync_event)(u32 sel);
    s32 (*start_process)(void);
    s32 (*capture_event)(u32 sel);
    s32 (*shadow_protect)(u32 sel, bool protect);
    struct disp_bootloader_info boot_info;
};

typedef void (*LCD_FUNC) (u32 sel);
struct disp_lcd_function {
    LCD_FUNC func;
    unsigned int delay; /* ms */
};

#define LCD_MAX_SEQUENCES 7
struct disp_lcd_flow {
    struct disp_lcd_function func[LCD_MAX_SEQUENCES];
    unsigned int func_num;
    unsigned int cur_step;
};

struct disp_lcd_panel_fun {
    void (*cfg_panel_info)(struct panel_extend_para *info);
    s32 (*cfg_open_flow)(u32 sel);
    s32 (*cfg_close_flow)(u32 sel);
    s32 (*lcd_user_defined_func)(u32 sel, u32 para1,
                      u32 para2, u32 para3);
    s32 (*set_bright)(u32 sel, u32 bright);
    /*check if panel is ok.return 0 if ok*/
    s32 (*esd_check)(u32 sel);
    /*reset panel flow*/
    s32 (*reset_panel)(u32 sel);
    /*see the definition of struct disp_lcd_esd_info */
    s32 (*set_esd_info)(struct disp_lcd_esd_info *p_info);
};

struct disp_enhance_para {
    /* basic adjust */
    u32 bright;
    u32 contrast;
    u32 saturation;
    u32 hue;
    u32 mode;
    /* ehnance */
    u32 sharp;      /* 0-off; 1~3-on. */
    u32 auto_contrast;  /* 0-off; 1~3-on. */
    u32 auto_color;     /* 0-off; 1-on. */
    u32 fancycolor_red; /* 0-Off; 1-2-on. */
    u32 fancycolor_green;   /* 0-Off; 1-2-on. */
    u32 fancycolor_blue;    /* 0-Off; 1-2-on. */
    struct disp_rect window;
    u32 enable;
};

struct disp_device {
    struct list_head list;
    /* data fields */
    char name[32];
    u32 disp;
    /* indicate the index of hw device(timing controller) */
    u32 hwdev_index;
    u32 fix_timing;
    enum disp_output_type type;
    struct disp_manager *manager;
    struct disp_video_timings timings;
    hal_work close_eink_panel_work;
    void *priv_data;

    /* function fileds  */
    /* init: script init && clock init && pwm init && register irq
     * exit: clock exit && unregister irq
     */
    s32 (*init)(struct disp_device *dispdev);
    s32 (*exit)(struct disp_device *dispdev);

    s32 (*set_manager)(struct disp_device *dispdev,
               struct disp_manager *mgr);
    s32 (*unset_manager)(struct disp_device *dispdev);

    s32 (*enable)(struct disp_device *dispdev);
    s32 (*fake_enable)(struct disp_device *dispdev);
    s32 (*sw_enable)(struct disp_device *dispdev);
    s32 (*disable)(struct disp_device *dispdev);
    s32 (*is_enabled)(struct disp_device *dispdev);
    s32 (*check_if_enabled)(struct disp_device *dispdev);
    s32 (*is_used)(struct disp_device *dispdev);
    s32 (*get_resolution)(struct disp_device *dispdev, u32 *xres,
                  u32 *yres);
    s32 (*get_dimensions)(struct disp_device *dispdev, u32 *width,
                  u32 *height);
    s32 (*set_timings)(struct disp_device *dispdev,
               struct disp_video_timings *timings);
    s32 (*get_timings)(struct disp_device *dispdev,
               struct disp_video_timings *timings);
    s32 (*check_timings)(struct disp_device *dispdev,
                 struct disp_video_timings *timings);
    s32 (*smooth_enable)(struct disp_device *dispdev);
    s32 (*detect)(struct disp_device *dispdev);
    s32 (*set_detect)(struct disp_device *dispdev, bool hpd);
    s32 (*get_status)(struct disp_device *dispdev);
    s32 (*get_fps)(struct disp_device *dispdev);
    /*
     * check if be in the safe period now,
     * safe period means the current line is less than the start_delay
     */
    bool (*is_in_safe_period)(struct disp_device *dispdev);
    u32 (*usec_before_vblank)(struct disp_device *dispdev);

    s32 (*get_input_csc)(struct disp_device *dispdev);
    s32 (*get_input_color_range)(struct disp_device *dispdev);
    s32 (*is_interlace)(struct disp_device *dispdev);

    /* power manager */
    s32 (*early_suspend)(struct disp_device *dispdev);
    s32 (*late_resume)(struct disp_device *dispdev);
    s32 (*suspend)(struct disp_device *dispdev);
    s32 (*resume)(struct disp_device *dispdev);

    s32 (*dump)(struct disp_device *dispdev, char *buf);

    /* HDMI /TV */
    s32 (*set_mode)(struct disp_device *dispdev, u32 mode);
    s32 (*get_mode)(struct disp_device *dispdev);
    s32 (*set_static_config)(struct disp_device *dispdev,
              struct disp_device_config *config);
    s32 (*get_static_config)(struct disp_device *dispdev,
              struct disp_device_config *config);
    s32 (*set_dynamic_config)(struct disp_device *dispdev,
              struct disp_device_dynamic_config *config);
    s32 (*get_dynamic_config)(struct disp_device *dispdev,
              struct disp_device_dynamic_config *config);

    s32 (*cec_standby_request)(struct disp_device *dispdev);
    s32 (*cec_send_one_touch_play)(struct disp_device *dispdev);
    /*
     * check_config_dirty
     * check if the config is not the same with current one
     */
    disp_config_update_t (*check_config_dirty)(struct disp_device *dispdev,
                   struct disp_device_config *config);
    s32 (*check_support_mode)(struct disp_device *dispdev, u32 mode);
    s32 (*set_func)(struct disp_device *dispdev,
            struct disp_device_func *func);
    s32 (*set_tv_func)(struct disp_device *dispdev,
               struct disp_tv_func *func);
    s32 (*set_enhance_mode)(struct disp_device *dispdev, u32 mode);

    /* LCD */
    s32 (*set_bright)(struct disp_device *dispdev, u32 bright);
    s32 (*get_bright)(struct disp_device *dispdev);
    s32 (*backlight_enable)(struct disp_device *dispdev);
    s32 (*backlight_disable)(struct disp_device *dispdev);
    s32 (*pwm_enable)(struct disp_device *dispdev);
    s32 (*pwm_disable)(struct disp_device *dispdev);
    s32 (*power_enable)(struct disp_device *dispdev, u32 power_id);
    s32 (*power_disable)(struct disp_device *dispdev, u32 power_id);
    s32 (*tcon_enable)(struct disp_device *dispdev);
    s32 (*tcon_disable)(struct disp_device *dispdev);
    s32 (*set_bright_dimming)(struct disp_device *dispdev, u32 dimming);

    struct disp_lcd_flow *(*get_open_flow)(struct disp_device *dispdev);
    struct disp_lcd_flow *(*get_close_flow)(struct disp_device *dispdev);
    s32 (*pin_cfg)(struct disp_device *dispdev, u32 bon);
    s32 (*set_gamma_tbl)(struct disp_device *dispdev, u32 *tbl,
                  u32 size);
    s32 (*enable_gamma)(struct disp_device *dispdev);
    s32 (*disable_gamma)(struct disp_device *dispdev);
    s32 (*set_color_temperature)(struct disp_device *dispdev, s32 color_temperature);
    s32 (*get_color_temperature)(struct disp_device *dispdev);
    s32 (*set_panel_func)(struct disp_device *lcd, char *name,
                  struct disp_lcd_panel_fun *lcd_cfg);
    s32 (*set_open_func)(struct disp_device *lcd, LCD_FUNC func,
                 u32 delay);
    s32 (*set_close_func)(struct disp_device *lcd, LCD_FUNC func,
                  u32 delay);
    s32 (*gpio_set_value)(struct disp_device *dispdev,
                  u32 io_index, u32 value);
    s32 (*gpio_set_direction)(struct disp_device *dispdev,
                  u32 io_index, u32 direction);
    s32 (*get_panel_info)(struct disp_device *dispdev,
                   struct disp_panel_para *info);
    void (*show_builtin_patten)(struct disp_device *dispdev, u32 patten);
};

/* manager */
struct disp_manager {
    /* data fields */
    char name[32];
    u32 disp;
    u32 num_chns;
    u32 num_layers;
    struct disp_device *device;
    struct disp_smbl *smbl;
    struct disp_enhance *enhance;
    struct disp_capture *cptr;

    struct list_head lyr_list;
#if defined(CONFIG_SUNXI_DISP2_FB_ROTATION_SUPPORT)
    struct disp_rotation_sw *rot_sw;
#endif

#ifdef SUPPORT_WB
    wait_queue_head_t write_back_queue;
    u32 write_back_finish;
#endif

    /* function fields */
    s32 (*enable)(struct disp_manager *mgr);
    s32 (*sw_enable)(struct disp_manager *mgr);
    s32 (*disable)(struct disp_manager *mgr);
    s32 (*is_enabled)(struct disp_manager *mgr);
    s32 (*blank)(struct disp_manager *mgr, bool blank);

    /* init: clock init && reg init && register irq
     * exit: clock exit && unregister irq
     */
    s32 (*init)(struct disp_manager *mgr);
    s32 (*exit)(struct disp_manager *mgr);

    s32 (*set_back_color)(struct disp_manager *mgr,
                  struct disp_color *bk_color);
    s32 (*get_back_color)(struct disp_manager *mgr,
                  struct disp_color *bk_color);
    s32 (*set_color_key)(struct disp_manager *mgr,
                 struct disp_colorkey *ck);
    s32 (*get_color_key)(struct disp_manager *mgr,
                 struct disp_colorkey *ck);

    s32 (*get_screen_size)(struct disp_manager *mgr, u32 *width,
                u32 *height);
    s32 (*set_screen_size)(struct disp_manager *mgr, u32 width,
                u32 height);
    s32 (*get_clk_rate)(struct disp_manager *mgr);

    /* layer mamage */
    s32 (*check_layer_zorder)(struct disp_manager *mgr,
                  struct disp_layer_config *config,
                  u32 layer_num);
    s32 (*set_layer_config)(struct disp_manager *mgr,
                struct disp_layer_config *config,
                unsigned int layer_num);
    s32 (*get_layer_config)(struct disp_manager *mgr,
                struct disp_layer_config *config,
                unsigned int layer_num);
    s32 (*set_layer_config2)(struct disp_manager *mgr,
                 struct disp_layer_config2 *config,
                 unsigned int layer_num);
    s32 (*get_layer_config2)(struct disp_manager *mgr,
                 struct disp_layer_config2 *config,
                 unsigned int layer_num);
    s32 (*force_set_layer_config)(struct disp_manager *mgr, struct disp_layer_config *config, unsigned int layer_num);
    s32 (*force_set_layer_config_exit)(struct disp_manager *mgr);
    s32 (*extend_layer_config)(struct disp_manager *mgr,
                   struct disp_layer_config *info,
                   unsigned int layer_num);
    s32 (*set_output_color_range)(struct disp_manager *mgr,
                      u32 color_range);
    s32 (*get_output_color_range)(struct disp_manager *mgr);
    s32 (*update_color_space)(struct disp_manager *mgr);
    s32 (*smooth_switch)(struct disp_manager *mgr);
    s32 (*set_palette)(struct disp_manager *mgr, struct disp_palette_config *config);
    s32 (*apply)(struct disp_manager *mgr);
    s32 (*force_apply)(struct disp_manager *mgr);
    s32 (*update_regs)(struct disp_manager *mgr);
    s32 (*sync)(struct disp_manager *mgr, bool sync);
    s32 (*tasklet)(struct disp_manager *mgr);

    /* debug interface, dump manager info */
    s32 (*dump)(struct disp_manager *mgr);
};

struct disp_layer {
    /* data fields */
    char name[32];
    u32 disp;
    u32 chn;
    u32 id;

    /* enum disp_layer_feat caps; */
    struct disp_manager *manager;
    struct list_head list;
    void *data;

    /* function fileds */
    s32 (*is_support_format)(struct disp_layer *layer,
                  enum disp_pixel_format fmt);
    s32 (*set_manager)(struct disp_layer *layer,
                struct disp_manager *mgr);
    s32 (*unset_manager)(struct disp_layer *layer);
    s32 (*check)(struct disp_layer *layer,
              struct disp_layer_config *config);
    s32 (*check2)(struct disp_layer *layer,
              struct disp_layer_config2 *config);
    s32 (*save_and_dirty_check)(struct disp_layer *layer,
                     struct disp_layer_config *config);
    s32 (*save_and_dirty_check2)(struct disp_layer *layer,
                     struct disp_layer_config2 *config);
    s32 (*get_config)(struct disp_layer *layer,
               struct disp_layer_config *config);
    s32 (*get_config2)(struct disp_layer *layer,
               struct disp_layer_config2 *config);
    s32 (*apply)(struct disp_layer *layer);
    s32 (*force_apply)(struct disp_layer *layer);
    s32 (*is_dirty)(struct disp_layer *layer);
    s32 (*dirty_clear)(struct disp_layer *layer);
    /* init: NULL
     * exit: NULL
     */
    s32 (*init)(struct disp_layer *layer);
    s32 (*exit)(struct disp_layer *layer);
    s32 (*get_frame_id)(struct disp_layer *layer);
    s32 (*dump)(struct disp_layer *layer);
};

struct disp_smbl {
    /* static fields */
    char *name;
    u32 disp;
    u32 backlight;
    struct disp_manager *manager;

    /*
     * The following functions do not block:
     *
     * is_enabled
     * set_layer_info
     * get_layer_info
     *
     * The rest of the functions may block and cannot be called from
     * interrupt context
     */

    s32 (*enable)(struct disp_smbl *smbl);
    s32 (*disable)(struct disp_smbl *smbl);
    bool (*is_enabled)(struct disp_smbl *smbl);
    s32 (*set_manager)(struct disp_smbl *smbl, struct disp_manager *mgr);
    s32 (*unset_manager)(struct disp_smbl *smbl);
    s32 (*update_backlight)(struct disp_smbl *smbl, unsigned int bl);

    /* init: NULL
     * exit: NULL
     */
    s32 (*init)(struct disp_smbl *smbl);
    s32 (*exit)(struct disp_smbl *smbl);

    s32 (*apply)(struct disp_smbl *smbl);
    s32 (*update_regs)(struct disp_smbl *smbl);
    s32 (*force_apply)(struct disp_smbl *smbl);
    s32 (*sync)(struct disp_smbl *smbl);
    s32 (*tasklet)(struct disp_smbl *smbl);

    s32 (*set_window)(struct disp_smbl *smbl, struct disp_rect *window);
    s32 (*get_window)(struct disp_smbl *smbl, struct disp_rect *window);
    s32 (*dump)(struct disp_smbl *smbl, char *buf);
};

struct disp_enhance {
    /* static fields */
    char *name;
    u32 disp;
    struct disp_manager *manager;

    /*
     * The following functions do not block:
     *
     * is_enabled
     * set_layer_info
     * get_layer_info
     *
     * The rest of the functions may block and cannot be called from
     * interrupt context
     */

    s32 (*enable)(struct disp_enhance *enhance);
    s32 (*disable)(struct disp_enhance *enhance);
    bool (*is_enabled)(struct disp_enhance *enhance);
    s32 (*set_manager)(struct disp_enhance *enhance,
                struct disp_manager *mgr);
    s32 (*unset_manager)(struct disp_enhance *enhance);

    /* init: NULL
     * exit: NULL
     */
    s32 (*init)(struct disp_enhance *enhance);
    s32 (*exit)(struct disp_enhance *enhance);

    s32 (*apply)(struct disp_enhance *enhance);
    s32 (*update_regs)(struct disp_enhance *enhance);
    s32 (*force_apply)(struct disp_enhance *enhance);
    s32 (*sync)(struct disp_enhance *enhance);
    s32 (*tasklet)(struct disp_enhance *enhance);

    /* power manager */
    s32 (*early_suspend)(struct disp_enhance *enhance);
    s32 (*late_resume)(struct disp_enhance *enhance);
    s32 (*suspend)(struct disp_enhance *enhance);
    s32 (*resume)(struct disp_enhance *enhance);

    s32 (*set_bright)(struct disp_enhance *enhance, u32 val);
    s32 (*set_saturation)(struct disp_enhance *enhance, u32 val);
    s32 (*set_contrast)(struct disp_enhance *enhance, u32 val);
    s32 (*set_hue)(struct disp_enhance *enhance, u32 val);
    s32 (*set_edge)(struct disp_enhance *enhance, u32 val);
    s32 (*set_detail)(struct disp_enhance *enhance, u32 val);
    s32 (*set_denoise)(struct disp_enhance *enhance, u32 val);
    s32 (*set_mode)(struct disp_enhance *enhance, u32 val);
    s32 (*set_window)(struct disp_enhance *enhance,
              struct disp_rect *window);
    s32 (*get_bright)(struct disp_enhance *enhance);
    s32 (*get_saturation)(struct disp_enhance *enhance);
    s32 (*get_contrast)(struct disp_enhance *enhance);
    s32 (*get_hue)(struct disp_enhance *enhance);
    s32 (*get_edge)(struct disp_enhance *enhance);
    s32 (*get_detail)(struct disp_enhance *enhance);
    s32 (*get_denoise)(struct disp_enhance *enhance);
    s32 (*get_mode)(struct disp_enhance *enhance);
    s32 (*get_window)(struct disp_enhance *enhance,
              struct disp_rect *window);
    s32 (*set_para)(struct disp_enhance *enhance,
            struct disp_enhance_para *para);
    s32 (*demo_enable)(struct disp_enhance *enhance);
    s32 (*demo_disable)(struct disp_enhance *enhance);
    s32 (*dump)(struct disp_enhance *enhance, char *buf);
};

struct disp_capture {
    char name[16];
    u32 disp;
    struct disp_manager *manager;

    s32 (*set_manager)(struct disp_capture *cptr,
                struct disp_manager *mgr);
    s32 (*unset_manager)(struct disp_capture *cptr);
    s32 (*start)(struct disp_capture *cptr);
    s32 (*commmit)(struct disp_capture *cptr,
            struct disp_capture_info *info);
    s32 (*commmit2)(struct disp_capture *cptr,
            struct disp_capture_info2 *info);
    s32 (*stop)(struct disp_capture *cptr);
    s32 (*sync)(struct disp_capture *cptr);
    s32 (*tasklet)(struct disp_capture *cptr);
    s32 (*init)(struct disp_capture *cptr);
    s32 (*exit)(struct disp_capture *cptr);
    /* 0: finish, other: fail/err */
    s32 (*query)(struct disp_capture *cptr);

    /* debug interface, dump capture info */
    s32 (*dump)(struct disp_capture *cptr, char *buf);
    /* inner interface */
    s32 (*apply)(struct disp_capture *cptr);
};

#if defined(CONFIG_SUNXI_DISP2_FB_ROTATION_SUPPORT)
struct disp_rotation_sw {
    u32 disp;
    u32 degree;
    struct disp_rectsz screen_size; /* virtual screen_size */

    struct disp_manager *manager;

    s32 (*init)(struct disp_rotation_sw *rot_sw);
    s32 (*exit)(struct disp_rotation_sw *rot_sw);
    s32 (*set_layer_degree)(struct disp_rotation_sw *rot_sw, u32 chn,
                u32 lyr_id, u32 degree);
    s32 (*get_layer_degree)(struct disp_rotation_sw *rot_sw, u32 chn,
                u32 lyr_id);
    s32 (*set_manager)(struct disp_rotation_sw *rot_sw,
               struct disp_manager *mgr);
    s32 (*unset_manager)(struct disp_rotation_sw *rot_sw);
    s32 (*apply)(struct disp_rotation_sw *rot_sw,
             struct disp_layer_config *lyr_config,
             struct disp_rect src_dirty_rect);
    s32 (*checkout)(struct disp_rotation_sw *rot_sw,
            struct disp_layer_config *lyr_config);
};
#endif

struct ee_img {
    unsigned long addr;
    unsigned int pitch;
    unsigned int w;     /* image width */
    unsigned int h;     /* image height */
};

struct rect_size {
    u32 width;
    u32 height;
    u32 align;
};

#if defined(CONFIG_EINK_PANEL_USED)
struct area_info {
    unsigned int x_top;
    unsigned int y_top;
    unsigned int x_bottom;
    unsigned int y_bottom;
};

struct eink_timing_param {
    unsigned int lbl;   /*  */
    unsigned int lel;   /*  */
    unsigned int lsl;
    unsigned int fbl;   /*  */
    unsigned int fel;   /*  */
    unsigned int fsl;   /*  */
    unsigned int width; /* image width */
    unsigned int height;    /* image height */
};

enum eink_flash_mode {
    LOCAL,
    GLOBAL,
    INIT
};

enum buf_use_state {
    FREE,
    USED
};

enum eink_update_mode {
    /* GLOBAL */
    EINK_INIT_MODE = 0x01,
    EINK_DU_MODE = 0x02,
    EINK_GC16_MODE = 0x04,
    EINK_A2_MODE = 0x10,
    EINK_GC16_LOCAL_MODE = 0x84,

    /* LOCAL */
    EINK_DU_RECT_MODE = 0x402,
    EINK_GC16_RECT_MODE = 0x404,
    EINK_A2_RECT_MODE = 0x410,
    EINK_GC16_LOCAL_RECT_MODE = 0x484,
};

struct eink_8bpp_image {
    enum eink_update_mode update_mode;
    enum eink_flash_mode flash_mode;
    enum buf_use_state state;
    void *vaddr;
    void *paddr;
    bool window_calc_enable;
    struct rect_size size;
    struct area_info update_area;
};

struct eink_init_param {
    bool used;
    u8 eink_moudule_type;
    u8 eink_version_type;
    u8 eink_ctrl_data_type;
    u8 eink_bits;       /*0->3bits,1->4bits,2->5bits */
    u8 eink_mode;       /*0->8data,1->16data */
    struct eink_timing_param timing;
    char wavefile_path[32];
};

enum eink_bit_num {
    EINK_BIT_1 = 0x01,
    EINK_BIT_2 = 0x02,
    EINK_BIT_3 = 0x03,
    EINK_BIT_4 = 0x04,
    EINK_BIT_5 = 0x05
};

/* #define EINK_FLUSH_TIME_TEST */

struct disp_eink_manager {
    unsigned int disp;
    unsigned int test;
    int tcon_flag;
    int eink_panel_temperature;

    unsigned int flush_continue_flag;
    struct tasklet_struct sync_tasklet;
    struct tasklet_struct decode_tasklet;
    wait_queue_head_t decode_taske_queue;
    struct work_struct decode_work;
    struct eink_private *private_data;
    struct disp_manager *mgr;
    struct eink_buffer_manager *buffer_mgr;
    struct pipeline_manager *pipeline_mgr;
    struct format_manager *convert_mgr;
    struct task_struct *detect_fresh_task;
    struct task_struct *debug_task;
    struct mutex standby_lock;
    int (*eink_update)(struct disp_eink_manager *manager,
                struct disp_layer_config_inner *config,
                unsigned int layer_num,
                enum eink_update_mode mode,
                struct area_info update_area);
    int (*enable)(struct disp_eink_manager *);
    int (*disable)(struct disp_eink_manager *);
    int (*op_skip)(struct disp_eink_manager *manager, u32 skip);
    int (*suspend)(struct disp_eink_manager *);
    int (*resume)(struct disp_eink_manager *);
    void (*clearwd)(struct disp_eink_manager *, int);
    /*for debug */
    int (*decode)(struct disp_eink_manager *, int);
    int (*set_temperature)(struct disp_eink_manager *manager,
                unsigned int temp);
    unsigned int (*get_temperature)(struct disp_eink_manager *manager);
};

struct image_format {
    enum disp_pixel_format format;
    unsigned int width;
    unsigned int height;
    unsigned long addr1;
    unsigned long addr2;
    unsigned long addr3;
};

struct format_manager {
    unsigned int disp;
    unsigned int irq_num;
    unsigned int write_back_finish;
    wait_queue_head_t write_back_queue;
    struct clk *clk;
    int (*enable)(unsigned int id);
    int (*disable)(unsigned int id);
    int (*start_convert)(unsigned int id,
                  struct disp_layer_config_inner *config,
                  unsigned int layer_num,
                  struct image_format *dest);
};
#endif
#endif
