/*
 * g2d_mixer_type/g2d_mixer_type.h
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef _G2D_MIXER_TYPE_H
#define _G2D_MIXER_TYPE_H

#define G2D_TOP        (0x00000)
#define G2D_MIXER      (0x00100)
#define G2D_BLD        (0x00400)
#define G2D_V0         (0x00800)
#define G2D_UI0        (0x01000)
#define G2D_UI1        (0x01800)
#define G2D_UI2        (0x02000)
#define G2D_WB         (0x03000)
#define G2D_VSU        (0x08000)
#define G2D_ROT        (0x28000)
#define G2D_GSU        (0x30000)


/*mixer overlay for video data define start*/
union g2d_mixer_ovl_attr {
	unsigned int dwval;
	struct {
		unsigned int lay_en:1;
		unsigned int alpha_mode:2;
		unsigned int res0:1;
		unsigned int lay_fillcolor_en:1;
		unsigned int res1:3;
		unsigned int lay_fbfmt:6;
		unsigned int res2:2;
		unsigned int lay_premul_ctl:2;
		unsigned int res3:6;
		unsigned int lay_glbalpha:8;
	} bits;
};

union g2d_mixer_ovl_mem {
	unsigned int dwval;
	struct {
		unsigned int lay_width:13;
		unsigned int res0:3;
		unsigned int lay_height:13;
		unsigned int res1:3;
	} bits;
};

union g2d_mixer_ovl_mem_coor {
	unsigned int dwval;
	struct {
		unsigned int lay_ycoor:16;
		unsigned int lay_xcoor:16;
	} bits;
};

union g2d_mixer_ovl_mem_high_addr {
	unsigned int dwval;
	struct {
		unsigned int lay_y_hadd:8;
		unsigned int lay_u_hadd:8;
		unsigned int lay_v_hadd:8;
		unsigned int res0:8;
	} bits;
};

union g2d_mixer_ovl_winsize {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int res0:3;
		unsigned int height:13;
		unsigned int res1:3;
	} bits;
};

union g2d_mixer_ovl_down_sample {
	unsigned int dwval;
	struct {
		unsigned int M:14;
		unsigned int res0:2;
		unsigned int N:14;
		unsigned int res1:2;
	} bits;
};

struct g2d_mixer_ovl_v_reg {
	/*0x00*/
	union g2d_mixer_ovl_attr ovl_attr;
	union g2d_mixer_ovl_mem ovl_mem;
	union g2d_mixer_ovl_mem_coor ovl_mem_coor;
	unsigned int ovl_mem_pitch0;
	/*0x10*/
	unsigned int ovl_mem_pitch1;
	unsigned int ovl_mem_pitch2;
	unsigned int ovl_mem_low_addr0;
	unsigned int ovl_mem_low_addr1;
	/*0x20*/
	unsigned int ovl_mem_low_addr2;
	unsigned int ovl_fill_color;
	union g2d_mixer_ovl_mem_high_addr ovl_mem_high_addr;
	union g2d_mixer_ovl_winsize ovl_winsize;
	/*0x30*/
	union g2d_mixer_ovl_down_sample hor_down_sample0;
	union g2d_mixer_ovl_down_sample hor_down_sample1;
	union g2d_mixer_ovl_down_sample ver_down_sample0;
	union g2d_mixer_ovl_down_sample ver_down_sample1;
};
/*mixer overlay for video data define end*/

/*mixer overlay for UI data define start*/

union g2d_mixer_ovl_u_attr {
	unsigned int dwval;
	struct {
		unsigned int lay_en:1;
		unsigned int alpha_mode:2;
		unsigned int res0:1;
		unsigned int lay_fillcolor_en:1;
		unsigned int res1:3;
		unsigned int lay_fbfmt:5;
		unsigned int res2:3;
		unsigned int lay_premul_ctl:2;
		unsigned int res3:6;
		unsigned int lay_glbalpha:8;
	} bits;
};
struct g2d_mixer_ovl_u_reg {
	/*0x00*/
	union g2d_mixer_ovl_u_attr ovl_attr;
	union g2d_mixer_ovl_mem ovl_mem;
	union g2d_mixer_ovl_mem_coor ovl_mem_coor;
	unsigned int ovl_mem_pitch0;
	/*0x10*/
	unsigned int ovl_mem_low_addr0;
	unsigned int ovl_fill_color;
	unsigned int ovl_mem_high_addr;
	union g2d_mixer_ovl_winsize ovl_winsize;
};
/*mixer overlay for UI data define end*/


/*mixer video scaler define start*/
union g2d_mixer_vs_ctrl {
	unsigned int dwval;
	struct {
		unsigned int en:1;
		unsigned int res0:7;
		unsigned int coef_access_sel:1;
		unsigned int res1:7;
		unsigned int filter_type:1;
		unsigned int res2:13;
		unsigned int core_rst:1;
		unsigned int bist_en:1;
	} bits;
};

union g2d_mixer_vs_out_size {
	unsigned int dwval;
	struct {
		unsigned int out_width:13;
		unsigned int res0:3;
		unsigned int out_height:13;
		unsigned int res1:3;
	} bits;
};

union g2d_mixer_vs_glb_alpha {
	unsigned int dwval;
	struct {
		unsigned int glb_alpha:8;
		unsigned int res0:24;
	} bits;
};

union g2d_mixer_vs_ch_size {
	unsigned int dwval;
	struct {
		unsigned int y_width:13;
		unsigned int res0:3;
		unsigned int y_height:13;
		unsigned int res1:3;
	} bits;
};

union g2d_mixer_vs_step {
	unsigned int dwval;
	struct {
		unsigned int res0:1;
		unsigned int frac:19;
		unsigned int integer:4;
		unsigned int res1:8;
	} bits;
};

union g2d_mixer_vs_filter_coeff {
	unsigned int dwval;
	struct {
		unsigned int coff0:8;
		unsigned int coff1:8;
		unsigned int coff2:8;
		unsigned int coff3:8;
	} bits;
};

struct g2d_mixer_video_scaler_reg {
	/*0x00*/
	union g2d_mixer_vs_ctrl vs_ctrl;
	unsigned int res0[15];
	/*0x40*/
	union g2d_mixer_vs_out_size out_size;
	union g2d_mixer_vs_glb_alpha glb_alpha;
	unsigned int res1[14];
	/*0x80*/
	union g2d_mixer_vs_ch_size y_ch_size;
	unsigned int res2;
	union g2d_mixer_vs_step y_hor_step;
	union g2d_mixer_vs_step y_ver_step;
	/*0x90*/
	union g2d_mixer_vs_step y_hor_phase;
	unsigned int res3;
	union g2d_mixer_vs_step y_ver_phase;
	unsigned int res4[9];
	/*0xc0*/
	union g2d_mixer_vs_ch_size c_ch_size;
	unsigned int res5;
	union g2d_mixer_vs_step c_hor_step;
	union g2d_mixer_vs_step c_ver_step;
	/*0xd0*/
	union g2d_mixer_vs_step c_hor_phase;
	unsigned int res6;
	union g2d_mixer_vs_step c_ver_phase;
	unsigned int res7[73];
	union g2d_mixer_vs_filter_coeff vs_y_ch_hor_filter_coef[32];
	unsigned int res8[32];
	union g2d_mixer_vs_filter_coeff vs_y_ch_ver_filter_coef[32];
	unsigned int res9[32];
	union g2d_mixer_vs_filter_coeff vs_c_ch_hor_filter_coef[32];
};
/*mixer video scaler define end*/

/*mixer video blender define start*/
union g2d_mixer_bld_en_ctrl {
	unsigned int dwval;
	struct {
		unsigned int p0_fcen:1;
		unsigned int p1_fcen:1;
		unsigned int res0:6;
		unsigned int p0_en:1;
		unsigned int p1_en:1;
		unsigned int res1:22;
	} bits;
};

union g2d_mixer_bld_mem_size {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int res0:3;
		unsigned int height:13;
		unsigned int res1:3;
	} bits;
};

union g2d_mixer_bld_mem_coor {
	unsigned int dwval;
	struct {
		unsigned int xcoor:16;
		unsigned int ycoor:16;
	} bits;
};

union g2d_mixer_bld_premulti_ctrl {
	unsigned int dwval;
	struct {
		unsigned int p0_alpha_mode:1;
		unsigned int p1_alpha_mode:1;
		unsigned int res0:30;
	} bits;
};

union g2d_mixer_bld_ctrl {
	unsigned int dwval;
	struct {
		unsigned int blend_pfs:4;
		unsigned int res0:4;
		unsigned int blend_pfd:4;
		unsigned int res1:4;
		unsigned int blend_afs:4;
		unsigned int res2:4;
		unsigned int blend_afd:4;
		unsigned int res3:4;
	} bits;
};

union g2d_mixer_bld_color_key {
	unsigned int dwval;
	struct {
		unsigned int key0_en:1;
		unsigned int key0_match_dir:2;
		unsigned int res0:29;
	} bits;
};

union g2d_mixer_bld_color_key_cfg {
	unsigned int dwval;
	struct {
		unsigned int key0b_match:1;
		unsigned int key0g_match:1;
		unsigned int key0y_match:1;
		unsigned int res0:29;
	} bits;
};


union g2d_mixer_bld_color_key_max {
	unsigned int dwval;
	struct {
		unsigned int max_b:8;
		unsigned int max_g:8;
		unsigned int max_r:8;
		unsigned int res0:8;
	} bits;
};

union g2d_mixer_bld_color_key_min {
	unsigned int dwval;
	struct {
		unsigned int min_b:8;
		unsigned int min_g:8;
		unsigned int min_r:8;
		unsigned int res0:8;
	} bits;
};

union g2d_mixer_bld_output_color {
	unsigned int dwval;
	struct {
		unsigned int premul_en:1;
		unsigned int alpha_mode:1;
		unsigned int res0:30;
	} bits;
};



union g2d_mixer_rop_ctrl {
	unsigned int dwval;
	struct {
		unsigned int type:1;
		unsigned int res0:3;
		unsigned int blue_bypass_en:1;
		unsigned int green_bypass_en:1;
		unsigned int red_bypass_en:1;
		unsigned int alpha_bypass_en:1;
		unsigned int blue_ch_sel:2;
		unsigned int green_ch_sel:2;
		unsigned int red_ch_sel:2;
		unsigned int alpha_ch_sel:2;
		unsigned int res1:16;
	} bits;
};

union g2d_mixer_rop_ch3_index0 {
	unsigned int dwval;
	struct {
		unsigned int index0node0:3;
		unsigned int index0node1:1;
		unsigned int index0node2:1;
		unsigned int index0node3:1;
		unsigned int index0node4:4;
		unsigned int index0node5:1;
		unsigned int index0node6:4;
		unsigned int index0node7:1;
		unsigned int ch0ign_en:1;
		unsigned int ch1ign_en:1;
		unsigned int ch2ign_en:1;
		unsigned int res0:13;
	} bits;
};

union g2d_mixer_bld_cs_ctrl {
	unsigned int dwval;
	struct {
		unsigned int cs0_en:1;
		unsigned int cs1_en:1;
		unsigned int cs2_en:1;
		unsigned int res0:29;
	} bits;
};

union g2d_mixer_bld_cs_coeff {
	unsigned int dwval;
	struct {
		unsigned int coeff:13;
		unsigned int res0:19;
	} bits;
};

union g2d_mixer_bld_cs_const {
	unsigned int dwval;
	struct {
		unsigned int const:20;
		unsigned int res0:12;
	} bits;
};


struct g2d_mixer_bld_reg {
	/*0x00*/
	union g2d_mixer_bld_en_ctrl bld_en_ctrl;
	unsigned int res0[3];
	/*0x10*/
	unsigned int bld_fill_color[2];
	unsigned int res1[2];
	/*0x20*/
	union g2d_mixer_bld_mem_size mem_size[2];
	unsigned int res2[2];
	/*0x30*/
	union g2d_mixer_bld_mem_coor mem_coor[2];
	unsigned int res3[2];
	/*0x40*/
	union g2d_mixer_bld_premulti_ctrl premulti_ctrl;
	unsigned int bld_backgroud_color;
	union g2d_mixer_bld_mem_size out_size;
	union g2d_mixer_bld_ctrl bld_ctrl;
	/*0x50*/
	union g2d_mixer_bld_color_key color_key;
	union g2d_mixer_bld_color_key_cfg color_key_cfg;
	union g2d_mixer_bld_color_key_max color_key_max;
	union g2d_mixer_bld_color_key_min color_key_min;
	/*0x60*/
	union g2d_mixer_bld_output_color out_color;
	unsigned int res4[7];
	/*0x80*/
	union g2d_mixer_rop_ctrl rop_ctrl;
	union g2d_mixer_rop_ch3_index0 ch3_index0;
	union g2d_mixer_rop_ch3_index0 ch3_index1;
	unsigned int res5[29];
	/*0x100*/
	union g2d_mixer_bld_cs_ctrl cs_ctrl;
	unsigned int res6[3];
	/*0x110*/
	union g2d_mixer_bld_cs_coeff csc0_coeff0_reg0;
	union g2d_mixer_bld_cs_coeff csc0_coeff0_reg1;
	union g2d_mixer_bld_cs_coeff csc0_coeff0_reg2;
	union g2d_mixer_bld_cs_const csc0_const0;
	/*0x120*/
	union g2d_mixer_bld_cs_coeff csc0_coeff1_reg0;
	union g2d_mixer_bld_cs_coeff csc0_coeff1_reg1;
	union g2d_mixer_bld_cs_coeff csc0_coeff1_reg2;
	union g2d_mixer_bld_cs_const csc0_const1;
	/*0x130*/
	union g2d_mixer_bld_cs_coeff csc0_coeff2_reg0;
	union g2d_mixer_bld_cs_coeff csc0_coeff2_reg1;
	union g2d_mixer_bld_cs_coeff csc0_coeff2_reg2;
	union g2d_mixer_bld_cs_const csc0_const2;
	/*0x140*/
	union g2d_mixer_bld_cs_coeff csc1_coeff0_reg0;
	union g2d_mixer_bld_cs_coeff csc1_coeff0_reg1;
	union g2d_mixer_bld_cs_coeff csc1_coeff0_reg2;
	union g2d_mixer_bld_cs_const csc1_const0;
	/*0x150*/
	union g2d_mixer_bld_cs_coeff csc1_coeff1_reg0;
	union g2d_mixer_bld_cs_coeff csc1_coeff1_reg1;
	union g2d_mixer_bld_cs_coeff csc1_coeff1_reg2;
	union g2d_mixer_bld_cs_const csc1_const1;
	/*0x160*/
	union g2d_mixer_bld_cs_coeff csc1_coeff2_reg0;
	union g2d_mixer_bld_cs_coeff csc1_coeff2_reg1;
	union g2d_mixer_bld_cs_coeff csc1_coeff2_reg2;
	union g2d_mixer_bld_cs_const csc1_const2;
	/*0x170*/
	union g2d_mixer_bld_cs_coeff csc2_coeff0_reg0;
	union g2d_mixer_bld_cs_coeff csc2_coeff0_reg1;
	union g2d_mixer_bld_cs_coeff csc2_coeff0_reg2;
	union g2d_mixer_bld_cs_const csc2_const0;
	/*0x180*/
	union g2d_mixer_bld_cs_coeff csc2_coeff1_reg0;
	union g2d_mixer_bld_cs_coeff csc2_coeff1_reg1;
	union g2d_mixer_bld_cs_coeff csc2_coeff1_reg2;
	union g2d_mixer_bld_cs_const csc2_const1;
	/*0x190*/
	union g2d_mixer_bld_cs_coeff csc2_coeff2_reg0;
	union g2d_mixer_bld_cs_coeff csc2_coeff2_reg1;
	union g2d_mixer_bld_cs_coeff csc2_coeff2_reg2;
	union g2d_mixer_bld_cs_const csc2_const2;
};
/*mixer video blender define end*/

/*mixer write back start*/
union g2d_mxier_wb_attr {
	unsigned int dwval;
	struct {
		unsigned int fmt:6;
		unsigned int res0:2;
		unsigned int round_en:1;
		unsigned int res1:23;
	} bits;
};

union g2d_mxier_wb_data_size {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int res0:3;
		unsigned int height:13;
		unsigned int res1:3;
	} bits;
};

struct g2d_mixer_write_back_reg {
	/*0x00*/
	union g2d_mxier_wb_attr wb_attr;
	union g2d_mxier_wb_data_size data_size;
	unsigned int pitch0;
	unsigned int pitch1;
	/*0x10*/
	unsigned int pitch2;
	unsigned int laddr0;
	unsigned int haddr0;
	unsigned int laddr1;
	/*0x20*/
	unsigned int haddr1;
	unsigned int laddr2;
	unsigned int haddr2;
};
/*mixer write back end*/

#endif /*End of file*/
