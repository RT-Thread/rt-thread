/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DE_RTMX_TYPE_H__
#define __DE_RTMX_TYPE_H__

/* for global control */
union __glb_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int rt_en:1;
        unsigned int r0:3;
        unsigned int finish_irq_en:1;
        unsigned int error_irq_en:1;
        unsigned int r1:2;
        unsigned int sync_rev:1;
        unsigned int flied_rev:1;
        unsigned int r2:2;
        unsigned int rtwb_port:2;
        unsigned int r3:18;
    } bits;
};
/* 0x0 */

union __glb_status_reg_t {
    unsigned int dwval;
    struct {
        unsigned int finish_irq:1;
        unsigned int error_irq:1;
        unsigned int r0:2;
        unsigned int busy_status:1;
        unsigned int error_status:1;
        unsigned int r1:2;
        unsigned int even_odd_flag:1;
        unsigned int r2:23;
    } bits;
};
/* 0x4 */

union __glb_dbuff_reg_t {
    unsigned int dwval;
    struct {
        unsigned int dbuff_rdy:1;
        unsigned int r0:31;
    } bits;
};
/* 0x8 */

union __glb_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int width:13;
        unsigned int r0:3;
        unsigned int height:13;
        unsigned int r1:3;
    } bits;
};
/* 0xc */

struct __glb_reg_t {
    union __glb_ctl_reg_t glb_ctl;
    union __glb_status_reg_t glb_status;
    union __glb_dbuff_reg_t glb_dbuff;
    union __glb_size_reg_t glb_size;
};

/* for video overlay */
union __vi_lay_attr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_en:1;
        unsigned int alpmode:2;
        unsigned int access_sw:1;
        unsigned int lay_fcolor_en:1;
        unsigned int r1:3;
        unsigned int lay_fmt:5;
        unsigned int r2:2;
        unsigned int ui_sel:1;
        unsigned int alpctl:2;
        unsigned int r3:2;
        unsigned int brust:3;
        unsigned int lay_top_down:1;
        unsigned int alpha:8;
    } bits;
};
/* 0x0+N*0x30(N=0,1,2,3) */

union __vi_lay_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_width:13;
        unsigned int r0:3;
        unsigned int lay_height:13;
        unsigned int r1:3;
    } bits;
};
/* 0x4+N*0x30(N=0,1,2,3) */

union __vi_lay_coor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_coorx:16;
        unsigned int lay_coory:16;
    } bits;
};
/* 0x8+N*0x30(N=0,1,2,3) */

union __vi_lay_pitch_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_pitch:32;
    } bits;
};
/* 0xc/0x010/0x014+N*0x30(N=0,1,2,3) */

union __vi_lay_top_laddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_top_laddr:32;
    } bits;
};
/* 0x018/0x01c/0x020+N*0x30(N=0,1,2,3) */

union __vi_lay_bot_laddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_bot_laddr:32;
    } bits;
};
/* 0x024/0x028/0x02c+N*0x30(N=0,1,2,3) */

union __vi_lay_fcolor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_vb:8;
        unsigned int lay_ug:8;
        unsigned int lay_yr:8;
        unsigned int r0:8;
    } bits;
};
/* 0x0c0+N*0x4(N=0,1,2,3) */

union __vi_lay_top_haddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay0_top_haddr:8;
        unsigned int lay1_top_haddr:8;
        unsigned int lay2_top_haddr:8;
        unsigned int lay3_top_haddr:8;
    } bits;
};
/* 0xd0~0x0xd8 */

union __vi_lay_bot_haddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay0_bot_haddr:8;
        unsigned int lay1_bot_haddr:8;
        unsigned int lay2_bot_haddr:8;
        unsigned int lay3_bot_haddr:8;
    } bits;
};
/* 0xdc~0xe4 */

union __vi_ovl_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int ovl_width:13;
        unsigned int r0:3;
        unsigned int ovl_height:13;
        unsigned int r1:3;
    } bits;
};
/* 0xe8~0xec */

union __vi_hori_ds_reg_t {
    unsigned int dwval;
    struct {
        unsigned int m:14;
        unsigned int r0:2;
        unsigned int n:14;
        unsigned int r1:2;
    } bits;
};
/* 0xf0~0xf4 */

union __vi_vert_ds_reg_t {
    unsigned int dwval;
    struct {
        unsigned int m:14;
        unsigned int r0:2;
        unsigned int n:14;
        unsigned int r1:2;
    } bits;
};
/* 0xf8~0xfc */

struct __vi_lay_reg_t {
    union __vi_lay_attr_reg_t lay_attr;
    union __vi_lay_size_reg_t lay_size;
    union __vi_lay_coor_reg_t lay_coor;
    union __vi_lay_pitch_reg_t lay_pitch[3];
    union __vi_lay_top_laddr_reg_t lay_top_laddr[3];
    union __vi_lay_bot_laddr_reg_t lay_bot_laddr[3];
};

struct __vi_ovl_reg_t {
    struct  __vi_lay_reg_t vi_lay_cfg[4];
    union __vi_lay_fcolor_reg_t vi_lay_fcolor[4];
    union __vi_lay_top_haddr_reg_t vi_lay_top_haddr[3];
    union __vi_lay_bot_haddr_reg_t vi_lay_bot_haddr[3];
    union __vi_ovl_size_reg_t vi_ovl_size[2];
    union __vi_hori_ds_reg_t vi_hori_ds[2];
    union __vi_vert_ds_reg_t vi_vert_ds[2];
};

/* for ui overlay */
union __ui_lay_attr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_en:1;
        unsigned int lay_alpmod:2;
        unsigned int access_sw:1;
        unsigned int lay_fcolor_en:1;
        unsigned int r1:3;
        unsigned int lay_fmt:5;
        unsigned int r2:3;
        unsigned int lay_alpctl:2;
        unsigned int r3:5;
        unsigned int lay_top_down:1;
        unsigned int lay_alpha:8;
    } bits;
};
/* 0x0+N*0x20(N=0,1,2,3) */

union __ui_lay_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_width:13;
        unsigned int r0:3;
        unsigned int lay_height:13;
        unsigned int r1:3;
    } bits;
};
/* 0x4+N*0x20(N=0,1,2,3) */

union __ui_lay_coor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_coorx:16;
        unsigned int lay_coory:16;
    } bits;
};
/* 0x8+N*0x20(N=0,1,2,3) */

union __ui_lay_pitch_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_pitch:32;
    } bits;
};
/* 0xc+N*0x20(N=0,1,2,3) */

union __ui_lay_top_laddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_top_laddr:32;
    } bits;
};
/* 0x10+N*0x20(N=0,1,2,3) */

union __ui_lay_bot_laddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_bot_laddr:32;
    } bits;
};
/* 0x14+N*0x20(N=0,1,2,3) */

union __ui_lay_fcolor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_blue:8;
        unsigned int lay_green:8;
        unsigned int lay_red:8;
        unsigned int lay_alpha:8;
    } bits;
};
/* 0x18+N*0x20(N=0,1,2,3) */

union __ui_lay_top_haddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay0_top_haddr:8;
        unsigned int lay1_top_haddr:8;
        unsigned int lay2_top_haddr:8;
        unsigned int lay3_top_haddr:8;
    } bits;
};
/* 0x80 */

union __ui_lay_bot_haddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay0_bot_haddr:8;
        unsigned int lay1_bot_haddr:8;
        unsigned int lay2_bot_haddr:8;
        unsigned int lay3_bot_haddr:8;
    } bits;
};
/* 0x84 */

union __ui_ovl_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int ovl_width:13;
        unsigned int r0:3;
        unsigned int ovl_height:13;
        unsigned int r1:3;
    } bits;
};
/* 0x88 */

struct __ui_lay_reg_t {
    union __ui_lay_attr_reg_t lay_attr;
    union __ui_lay_size_reg_t lay_size;
    union __ui_lay_coor_reg_t lay_coor;
    union __ui_lay_pitch_reg_t lay_pitch;
    union __ui_lay_top_laddr_reg_t lay_top_laddr;
    union __ui_lay_bot_laddr_reg_t lay_bot_laddr;
    union __ui_lay_fcolor_reg_t lay_fcolor;
    unsigned int r0;
};

struct __ui_ovl_reg_t {
    struct __ui_lay_reg_t ui_lay_cfg[4];
    union __ui_lay_top_haddr_reg_t ui_lay_top_haddr;
    union __ui_lay_bot_haddr_reg_t ui_lay_bot_haddr;
    union __ui_ovl_size_reg_t ui_ovl_size;
};

/* for alpha blending     */
union __bld_fcolor_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int p0_fcolor_en:1;
        unsigned int p1_fcolor_en:1;
        unsigned int p2_fcolor_en:1;
        unsigned int p3_fcolor_en:1;
        unsigned int p4_fcolor_en:1;
        unsigned int r0:3;
        unsigned int p0_en:1;
        unsigned int p1_en:1;
        unsigned int p2_en:1;
        unsigned int p3_en:1;
        unsigned int p4_en:1;
        unsigned int r1:19;
    } bits;
};
/* 0x0 */

union __bld_fcolor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int blue:8;
        unsigned int green:8;
        unsigned int red:8;
        unsigned int alpha:8;
    } bits;
};
/* 0x4+N*0x10(N=0,1,2,3,4) */

union __bld_isize_reg_t {
    unsigned int dwval;
    struct {
        unsigned int width:13;
        unsigned int r0:3;
        unsigned int height:13;
        unsigned int r1:3;
    } bits;
};
/* 0x8+N*0x10(N=0,1,2,3,4) */

union __bld_offset_reg_t {
    unsigned int dwval;
    struct {
        unsigned int coorx:16;
        unsigned int coory:13;
    } bits;
};
/* 0xc+N*0x10(N=0,1,2,3,4) */

union __bld_route_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int ch0_routr_ctl:4;
        unsigned int ch1_routr_ctl:4;
        unsigned int ch2_routr_ctl:4;
        unsigned int ch3_routr_ctl:4;
        unsigned int ch4_routr_ctl:4;
        unsigned int r0:12;
    } bits;
};

union __bld_premultiply_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int p0_alpha_mode:1;
        unsigned int p1_alpha_mode:1;
        unsigned int p2_alpha_mode:1;
        unsigned int p3_alpha_mode:1;
        unsigned int p4_alpha_mode:1;
        unsigned int r0:27;
    } bits;
};

union __bld_bkcolor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int blue:8;
        unsigned int green:8;
        unsigned int red:8;
        unsigned int alpha:8;
    } bits;
};

union __bld_output_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int width:13;
        unsigned int r0:3;
        unsigned int height:13;
        unsigned int r1:3;
    } bits;
};

union __bld_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int pixel_fs:4;
        unsigned int r0:4;
        unsigned int pixel_fd:4;
        unsigned int r1:4;
        unsigned int alpha_fs:4;
        unsigned int r2:4;
        unsigned int alpha_fd:4;
        unsigned int r3:4;
    } bits;
};

union __bld_colorkey_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int key0_en:1;
        unsigned int key0_dir:2;
        unsigned int r0:1;
        unsigned int key1_en:1;
        unsigned int key1_dir:2;
        unsigned int r1:1;
        unsigned int key2_en:1;
        unsigned int key2_dir:2;
        unsigned int r2:1;
        unsigned int key3_en:1;
        unsigned int key3_dir:2;
        unsigned int r3:17;
    } bits;
};

union __bld_colorkey_cfg_reg_t {
    unsigned int dwval;
    struct {
        unsigned int key0_blue:1;
        unsigned int key0_green:1;
        unsigned int key0_red:1;
        unsigned int r0:5;
        unsigned int key1_blue:1;
        unsigned int key1_green:1;
        unsigned int key1_red:1;
        unsigned int r1:5;
        unsigned int key2_blue:1;
        unsigned int key2_green:1;
        unsigned int key2_red:1;
        unsigned int r2:5;
        unsigned int key3_blue:1;
        unsigned int key3_green:1;
        unsigned int key3_red:1;
        unsigned int r3:5;
    } bits;
};

union __bld_colorkey_max_reg_t {
    unsigned int dwval;
    struct {
        unsigned int max_blue:8;
        unsigned int max_green:8;
        unsigned int max_red:8;
        unsigned int r0:8;
    } bits;
};

union __bld_colorkey_min_reg_t {
    unsigned int dwval;
    struct {
        unsigned int min_blue:8;
        unsigned int min_green:8;
        unsigned int min_red:8;
        unsigned int r0:8;
    } bits;
};

union __bld_out_color_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int premultiply_en:1;
        unsigned int interlace_en:1;
        unsigned int r0:30;
    } bits;
};

struct __bld_pipe_reg_t {
    union __bld_fcolor_reg_t fcolor;
    union __bld_isize_reg_t insize;
    union __bld_offset_reg_t offset;
    unsigned int r0;
};

struct __bld_reg_t {
    union __bld_fcolor_ctl_reg_t bld_fcolor_ctl;
    struct __bld_pipe_reg_t bld_pipe_attr[5];
    unsigned int r0[11];
    union __bld_route_ctl_reg_t bld_route_ctl;
    union __bld_premultiply_ctl_reg_t bld_premultiply_ctl;
    union __bld_bkcolor_reg_t bld_bkcolor;
    union __bld_output_size_reg_t bld_output_size;
    union __bld_ctl_reg_t bld_mode[4];
    unsigned int r1[4];
    union __bld_colorkey_ctl_reg_t bld_ck_ctl;
    union __bld_colorkey_cfg_reg_t bld_ck_cfg;
    unsigned int r2[2];
    union __bld_colorkey_max_reg_t bld_ck_max[4];
    unsigned int r3[4];
    union __bld_colorkey_min_reg_t bld_ck_min[4];
    unsigned int r4[3];
    union __bld_out_color_ctl_reg_t bld_out_ctl;
};

union __lbc_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lbc_en:1;
        unsigned int lbc_fcen:1;
        unsigned int alpmode:2;
        unsigned int clk_gate:1;
        unsigned int is_lossy:1;
        unsigned int r0:2;
        unsigned int rc_en:1;
        unsigned int r1:15;
        unsigned int alpha:8;
    } bits;
};

union __lbc_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lay_width:12;
        unsigned int r0:4;
        unsigned int lay_hight:12;
        unsigned int r1:4;
    } bits;
};

union __lbc_crop_coor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int left_crop:16;
        unsigned int top_crop:16;
    } bits;
};

union __lbc_crop_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int width_crop:12;
        unsigned int r0:4;
        unsigned int hight_crop:12;
        unsigned int r1:4;
    } bits;
};

union __lbc_laddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int laddr;
    } bits;
};

union __lbc_haddr_reg_t {
    unsigned int dwval;
    struct {
        unsigned int haddr:8;
        unsigned int r0:24;
    } bits;
};

union __lbc_seg_reg_t {
    unsigned int dwval;
    struct {
        unsigned int pitch:16;
        unsigned int seg_bit:16;
    } bits;
};

union __lbc_ovl_size_reg_t {
    unsigned int dwval;
    struct {
        unsigned int width_ovl:12;
        unsigned int r0:4;
        unsigned int height_ovl:12;
        unsigned int r1:4;
    } bits;
};

union __lbc_ovl_coor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int ovl_coorx:16;
        unsigned int ovl_coory:16;
    } bits;
};

union __lbc_fcolor_reg_t {
    unsigned int dwval;
    struct {
        unsigned int lbc_fc;
    } bits;
};

union __ovl_palette {
    unsigned int dwval;
    struct {
        unsigned int blue:8;
        unsigned int green:8;
        unsigned int red:8;
        unsigned int alpha:8;
    } bits;
};
struct  __ovl_palette_reg_t {
    union __ovl_palette val[PALETTE_SIZE];
};

struct __lbc_ovl_reg_t {
    union __lbc_ctl_reg_t lbc_ctl;
    union __lbc_size_reg_t lbc_v_size;
    union __lbc_crop_coor_reg_t lbc_crop_coor;
    union __lbc_crop_size_reg_t lbc_crop_size;
    union __lbc_laddr_reg_t lbc_laddr;
    union __lbc_haddr_reg_t lbc_haddr;
    union __lbc_seg_reg_t lbc_seg;
    union __lbc_ovl_size_reg_t lbc_ovl_size;
    union __lbc_ovl_coor_reg_t lbc_lay_coor;
    union __lbc_fcolor_reg_t lbc_fcolor;
};
union __glb_dither_ctl_reg_t {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int fmt:3;
        unsigned int mode:4;
        unsigned int fifo_3d:1;
    } bits;

};

union __glb_autoclk_reg_t {
    unsigned int dwval;
    struct {
        unsigned int en:1;
        unsigned int r0:31;
    } bits;

};

struct __glb_dither_reg_t {
    union __glb_autoclk_reg_t auto_clk;
    union __glb_dither_ctl_reg_t dither;
};
struct __rtmx_reg_t {
    struct __glb_reg_t *glb_ctl;
    struct __glb_dither_reg_t *dither_ctl;
    struct __bld_reg_t *bld_ctl;
    struct __vi_ovl_reg_t *vi_ovl[VI_CHN_NUM];
    struct __ui_ovl_reg_t *ui_ovl[UI_CHN_NUM];
    struct __lbc_ovl_reg_t *lbc_ovl[VI_CHN_NUM];
    struct __ovl_palette_reg_t *ui_palette[UI_CHN_NUM];
    struct __ovl_palette_reg_t *vi_palette[VI_CHN_NUM];
};

#endif
