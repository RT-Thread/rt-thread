/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file ipu_common.h
 * @brief common macro and data structre defination of IPU.
 * @ingroup diag_ipu
 */

#ifndef __IPU_COMMON_H__
#define __IPU_COMMON_H__

#include "sdk.h"
#include "sdk_types.h"
#include "ipu_reg_def.h"
#include "buffers.h"
#include "ldb/ldb_def.h"
#include "registers/regsipu.h"

#define FRAME_MAX_WIDTH		1920
#define FRAME_MAX_HEIGHT	1088

#define CPMEM_WORD0_OFFSET	0x0
#define CPMEM_WORD1_OFFSET	0x20

enum {
    IDMAC_SINGLE_BUFFER = 0x0,
    IDMAC_DOUBLE_BUFFER = 0x1,
};

enum {
    RGB,
    YUV,
};

enum {
    NO_CSC,
    RGB_YUV,
    YUV_RGB,
};

enum {
    IPU1_ERR = 37,
    IPU1_SYNC = 38,
    IPU2_ERR = 39,
    IPU2_SYNC = 40,
};

enum {
    IPU_ERR_INTERRUPT,
    IPU_SYNC_INTERRUPT,
};

// DI counter definitions
#define DI_COUNTER_BASECLK 	 	0
#define DI_COUNTER_IHSYNC   	1
#define DI_COUNTER_OHSYNC   	2
#define DI_COUNTER_OVSYNC   	3
#define DI_COUNTER_ALINE    	4
#define DI_COUNTER_ACLOCK   	5

// IDMAC defines
#define INTERLEAVED_MODE 		0
#define NON_INTERLEAVED_MODE 	1

#define SHIFT_DISABLE 			0
#define SHIFT_ENABLE  			1

#define CSC_ENABLE				1
#define CSC_DISABLE				0

enum {
    VDI_C_CH_420 = 0x00000000,
    VDI_C_CH_422 = 0x00000002,
    VDI_C_MOT_SEL_FULL = 0x00000008,
    VDI_C_MOT_SEL_LOW = 0x00000004,
    VDI_C_MOT_SEL_MED = 0x00000000,
    VDI_C_BURST_SIZE1_4 = 0x00000030,
    VDI_C_BURST_SIZE2_4 = 0x00000300,
    VDI_C_BURST_SIZE3_4 = 0x00003000,
    VDI_C_VWM1_SET_1 = 0x00000000,
    VDI_C_VWM1_CLR_2 = 0x00080000,
    VDI_C_VWM3_SET_1 = 0x00000000,
    VDI_C_VWM3_CLR_2 = 0x02000000,
    VDI_C_TOP_FIELD_MAN_1 = 0x40000000,
    VDI_C_TOP_FIELD_AUTO_1 = 0x80000000,
};

typedef enum {
    VDI_MED_MOTION = 0,
    VDI_LOW_MOTION = 1,
    VDI_HIGH_MOTION = 2,
} ips_motion_sel_e;

typedef enum {
    IPS_FIELD_INTERLACED_TB,
    IPS_FIELD_INTERLACED_BT,
} ips_field_mode_e;

struct ipu_cpmem_word {
    uint32_t data[5];
    uint32_t res[3];
};

typedef struct ipu_cpmem {
    struct ipu_cpmem_word word[2];
} ipu_cpmem_t;

#define ipu_cpmem_addr(ipu, ch) ({ \
	uint32_t temp = (uint32_t)(((struct ipu_cpmem *)(REGS_IPU_BASE(ipu)+IPU_MEMORY_OFFSET)) + (ch)); \
		temp;\
})

#define _param_word(base, w) \
	(((struct ipu_cpmem *)(base))->word[(w)].data)

/*define non-interleaved channel descriptor.
	p1 - word 0 or 1
	p2 - offset
	p3 - width
*/
#define NON_INTERLEAVED_XV 		0, 0, 10
#define NON_INTERLEAVED_YV 		0, 10, 9
#define NON_INTERLEAVED_XB 		0, 19,13
#define NON_INTERLEAVED_YB 		0, 32,12
#define NON_INTERLEAVED_NSBB 	0, 44, 1
#define NON_INTERLEAVED_CF 		0, 45, 1
#define NON_INTERLEAVED_UBO 	0, 46,22
#define NON_INTERLEAVED_VBO 	0, 68,22
#define NON_INTERLEAVED_IOX 	0, 90, 4
#define NON_INTERLEAVED_RDRW 	0, 94, 1
#define NON_INTERLEAVED_SO 		0, 113,1
#define NON_INTERLEAVED_BNDM  	0, 114,3
#define NON_INTERLEAVED_BM 		0, 117,2
#define NON_INTERLEAVED_ROT 	0, 119,1
#define NON_INTERLEAVED_HF 		0, 120,1
#define NON_INTERLEAVED_VF 		0, 121,1
#define NON_INTERLEAVED_THE 	0, 122,1
#define NON_INTERLEAVED_CAP 	0, 123,1
#define NON_INTERLEAVED_CAE 	0, 124,1
#define NON_INTERLEAVED_FW 		0, 125,13
#define NON_INTERLEAVED_FH 		0, 138,12
#define NON_INTERLEAVED_EBA0 	1, 0, 29
#define NON_INTERLEAVED_EBA1 	1, 29,29
#define NON_INTERLEAVED_ILO 	1, 58,20
#define NON_INTERLEAVED_NPB 	1, 78, 7
#define NON_INTERLEAVED_PFS 	1, 85, 4
#define NON_INTERLEAVED_ALU 	1, 89, 1
#define NON_INTERLEAVED_ALBM 	1, 90, 2
#define NON_INTERLEAVED_ID 		1, 93, 2
#define NON_INTERLEAVED_TH 		1, 95, 7
#define NON_INTERLEAVED_SLY 	1, 102,14
#define NON_INTERLEAVED_WID3 	1, 125,3
#define NON_INTERLEAVED_SLUV 	1, 128,14
#define NON_INTERLEAVED_CRE 	1, 149,1

/*define interleaved channel descriptor.
	p1 - word 0 or 1
	p2 - offset
	p3 - width
*/
#define INTERLEAVED_XV 		0, 0, 10
#define INTERLEAVED_YV 		0, 10, 9
#define INTERLEAVED_XB 		0, 19,13
#define INTERLEAVED_YB 		0, 32,12
#define INTERLEAVED_NSBB 	0, 44, 1
#define INTERLEAVED_CF 		0, 45, 1
#define INTERLEAVED_SX 		0, 46,12
#define INTERLEAVED_SY 		0, 58,11
#define INTERLEAVED_NS 		0, 69,10
#define INTERLEAVED_SDX 	0, 79, 7
#define INTERLEAVED_SM 		0, 86,10
#define INTERLEAVED_SCC 	0, 96, 1
#define INTERLEAVED_SCE 	0, 97, 1
#define INTERLEAVED_SDY 	0, 98, 7
#define INTERLEAVED_SDRX 	0, 105,1
#define INTERLEAVED_SDRY 	0, 106,1
#define INTERLEAVED_BPP 	0, 107,3
#define INTERLEAVED_DECSEL 	0, 110,2
#define INTERLEAVED_DIM 	0, 112,1
#define INTERLEAVED_SO 		0, 113,1
#define INTERLEAVED_BNDM  	0, 114,3
#define INTERLEAVED_BM 		0, 117,2
#define INTERLEAVED_ROT 	0, 119,1
#define INTERLEAVED_HF 		0, 120,1
#define INTERLEAVED_VF 		0, 121,1
#define INTERLEAVED_THE 	0, 122,1
#define INTERLEAVED_CAP 	0, 123,1
#define INTERLEAVED_CAE 	0, 124,1
#define INTERLEAVED_FW 		0, 125,13
#define INTERLEAVED_FH 		0, 138,12
#define INTERLEAVED_EBA0 	1, 0, 29
#define INTERLEAVED_EBA1 	1, 29,29
#define INTERLEAVED_ILO 	1, 58,20
#define INTERLEAVED_NPB 	1, 78, 7
#define INTERLEAVED_PFS 	1, 85, 4
#define INTERLEAVED_ALU 	1, 89, 1
#define INTERLEAVED_ALBM 	1, 90, 3
#define INTERLEAVED_ID 		1, 93, 2
#define INTERLEAVED_TH 		1, 95, 7
#define INTERLEAVED_SL 		1, 102,14
#define INTERLEAVED_WID0 	1, 116,3
#define INTERLEAVED_WID1 	1, 119,3
#define INTERLEAVED_WID2 	1, 122,3
#define INTERLEAVED_WID3 	1, 125,3
#define INTERLEAVED_OFF0 	1, 128,5
#define INTERLEAVED_OFF1 	1, 133,5
#define INTERLEAVED_OFF2 	1, 138,5
#define INTERLEAVED_OFF3 	1, 143,5
#define INTERLEAVED_SXYS 	1, 148,1
#define INTERLEAVED_CRE 	1, 149,1
#define INTERLEAVED_DECSEL2	1, 150,1

/*common definition for interleaved and non-interleaved channel descriptor.*/
#define CPMEM_XV 		NON_INTERLEAVED_XV
#define CPMEM_YV 		NON_INTERLEAVED_YV
#define CPMEM_XB 		NON_INTERLEAVED_XB
#define CPMEM_YB 		NON_INTERLEAVED_YB
#define CPMEM_NSBB 		NON_INTERLEAVED_NSBB
#define CPMEM_CF 		NON_INTERLEAVED_CF
#define CPMEM_SO 		NON_INTERLEAVED_SO
#define CPMEM_BNDM  	NON_INTERLEAVED_BNDM
#define CPMEM_BM 		NON_INTERLEAVED_BM
#define CPMEM_ROT 		NON_INTERLEAVED_ROT
#define CPMEM_HF 		NON_INTERLEAVED_HF
#define CPMEM_VF 		NON_INTERLEAVED_VF
#define CPMEM_THE 		NON_INTERLEAVED_THE
#define CPMEM_CAP 		NON_INTERLEAVED_CAP
#define CPMEM_CAE 		NON_INTERLEAVED_CAE
#define CPMEM_FW 		NON_INTERLEAVED_FW
#define CPMEM_FH 		NON_INTERLEAVED_FH
#define CPMEM_EBA0 		NON_INTERLEAVED_EBA0
#define CPMEM_EBA1 		NON_INTERLEAVED_EBA1
#define CPMEM_ILO 		NON_INTERLEAVED_ILO
#define CPMEM_NPB 		NON_INTERLEAVED_NPB
#define CPMEM_PFS 		NON_INTERLEAVED_PFS
#define CPMEM_ALU 		NON_INTERLEAVED_ALU
#define CPMEM_ALBM 		NON_INTERLEAVED_ALBM
#define CPMEM_ID 		NON_INTERLEAVED_ID
#define CPMEM_TH 		NON_INTERLEAVED_TH
#define CPMEM_CRE 		NON_INTERLEAVED_CRE

enum disp_port {
    IPU1_DI0,
    IPU1_DI1,
    IPU2_DI0,
    IPU2_DI1,
};

typedef struct dc_microcode {
    int32_t addr;
    int32_t stop;
    int32_t opcode;
    int32_t lf;
    int32_t af;
    int32_t operand;
    int32_t mapping;
    int32_t waveform;
    int32_t gluelogic;
    int32_t sync;
} dc_microcode_t;

enum dc_event {
    NL,
    NF,
    NFIELD,
    DCEOF,
    EOFIELD,
    EOL,
    NEW_CHAN,
    NEW_ADDR,
    NEW_DATA,
};

enum dc_opcode {
    HLG,
    WRG,
    HLOA,
    WROA,
    HLOD,
    WROD,
    HLOAR,
    WROAR,
    HLODR,
    WRODR,
    WRBC,
    WCLK,
    WSTSI,
    WSTSII,
    WSTSIII,
    RD,
    WACK,
    MSK,
    HMA,
    HMA1,
    BMA,
};

enum {
    CSI_TO_MEM_CH0 = 0,
    CSI_TO_MEM_CH1 = 1,
    CSI_TO_MEM_CH2 = 2,
    CSI_TO_MEM_CH3 = 3,
    MEM_TO_VDI_CH8 = 8,
    MEM_TO_VDI_CH9 = 9,
    MEM_TO_VDI_CH10 = 10,
    MEM_TO_IC_PP_RES_CH11 = 11,
    MEM_TO_IC_PRP_RES_CH12 = 12,
    VDI_TO_MEM_CH13 = 13,
    MEM_TO_IC_PPR_GPLANE_CH14 = 14,
    MEM_TO_IC_PP_GPLANE_CH15 = 15,
    MEM_TO_IC_PRP_ALPHA_CH17 = 17,
    MEM_TO_IC_PRP_ALPHA_CH18 = 18,
    IC_PRPENC_RES_TO_MEM_CH20 = 20,
    IC_PRPVF_RES_TO_MEM_CH21 = 21,
    IC_PP_RES_TO_MEM_CH22 = 22,
    MEM_TO_DP_BG_CH23 = 23,
    MEM_TO_DP_FG_CH27 = 27,
    MEM_TO_DC_CH28 = 28,
    MEM_TO_IC_PRPENC_ROT_CH45 = 45,
    MEM_TO_IC_PRPVF_ROT_CH46 = 46,
    MEM_TO_IC_PP_ROT_CH47 = 47,
    IC_PRPENC_ROT_TO_MEM_CH48 = 48,
    IC_PRPVF_ROT_TO_MEM_CH49 = 49,
    IC_PP_ROT_TO_MEM_CH50 = 50,
};

enum ic_task_type {
    PrP_ENC_TASK = 0,
    PrP_VF_TASK,
    PP_TASK,
    IC_CMB,
    IC_CSC1,
    IC_CSC2,
    IC_PP,
    IC_PRPENC,
    IC_PRPVF,
    IC_ROT,
};

typedef enum {
    NON_INTERLEAVED_YUV444 = 0x0,
    NON_INTERLEAVED_YUV422 = 0x1,
    NON_INTERLEAVED_YUV420 = 0x2,
    PARTIAL_INTERLEAVED_YUV422 = 0x3,
    PARTIAL_INTERLEAVED_YUV420 = 0x4,
    INTERLEAVED_LUT = 0x5,
    INTERLEAVED_GENERIC = 0x6,
    INTERLEAVED_ARGB8888 = 0x7 | (0 << 4),
    INTERLEAVED_RGB = 0x7,
    INTERLEAVED_RGB565 = 0x7 | (1 << 4),
    INTERLEAVED_Y1U1Y2V1 = 0x8,
    INTERLEAVED_Y2U1Y1V1 = 0x9,
    INTERLEAVED_U1Y1V1Y2 = 0xA,
    INTERLEAVED_U1Y2V1Y1 = 0xB,
} ips_dma_colorimetry_e;

typedef enum {
    DCMAP_RGB565,
    DCMAP_RGB666,
    DCMAP_RGB666H,
    DCMAP_RGB666L,
    DCMAP_RGB888,
    DCMAP_GBR888,
    DCMAP_BRG888,
    DCMAP_YUV888,
    DCMAP_UVY888,
    DCMAP_VYU888,
    DCMAP_RGBA8888,
    DCMAP_YUVA8888,
} ips_dcmap_colorimetry_e;

typedef enum {
    CSI_YUV444 = 0,
    CSI_YUYV,
    CSI_UYVY,
    CSI_Gereric,
    CSI_RGB565,
    CSI_RGB555,
    CSI_RGB444,
    CSI_JPEG,
} ips_csi_colorimetry_e;

typedef enum {
    CSI_CLK_MODE_GATED_CLK = 0,
    CSI_CLK_MODE_NONGATED_CLK,
    CSI_CLK_MODE_BT656_PROGRESSIVE,
    CSI_CLK_MODE_BT656_INTERLACED,
    CSI_CLK_MODE_BT1120_PROGRESSIVE_DDR,
    CSI_CLK_MODE_BT1120_PROGRESSIVE_SDR,
    CSI_CLK_MODE_BT1120_INTERLACED_DDR,
    CSI_CLK_MODE_BT1120_INTERLACED_SDR,
} ips_csi_clk_mode_e;

enum disp_dev_flag {
    CLAA_WVGA,
    BOUNDARYDEV_WVGA,
    TRULY_MIPI_TFT480800,
    HannStar_XGA_LVDS,
    VGAOUT_XGA,
    HDMI_720P60,
    HDMI_1080P60,
    SII9022_1080P60,
};

enum {
    DMFC_FIFO_512X128,
    DMFC_FIFO_256X128,
    DMFC_FIFO_128X128,
    DMFC_FIFO_64X128,
    DMFC_FIFO_32X128,
    DMFC_FIFO_16X128,
    DMFC_FIFO_8X128,
    DMFC_FIFO_4X128,
};

enum {
    DMFC_BURST_32X128,
    DMFC_BURST_16X128,
    DMFC_BURST_8X128,
    DMFC_BURST_4X128,
};

enum {
    CSI_PARALLEL,
    CSI_MIPI,
    CSI_BT656_NTSC_PROGRESSIVE,
    CSI_BT656_PAL_PROGRESSIVE,
    CSI_BT656_NTSC_INTERLACED,
    CSI_BT656_PAL_INTERLACED,
    CSI_TEST_MODE,
};

typedef struct {
    char panel_name[32];
    uint32_t panel_id;
    uint32_t panel_type;
    uint32_t colorimetry;
    uint32_t refresh_rate;
    uint32_t width;
    uint32_t height;
    uint32_t pixel_clock;
    uint32_t hsync_start_width;
    uint32_t hsync_width;
    uint32_t hsync_end_width;
    uint32_t vsync_start_width;
    uint32_t vsync_width;
    uint32_t vsync_end_width;
    uint32_t delay_h2v;
    uint32_t interlaced;
    uint32_t clk_sel;
    uint32_t clk_pol;
    uint32_t hsync_pol;
    uint32_t vsync_pol;
    uint32_t drdy_pol;
    uint32_t data_pol;
     int32_t(*panel_init) (int32_t * arg);
     int32_t(*panel_deinit) (void);
} ips_dev_panel_t;

typedef struct {
    uint32_t channel;
    uint32_t addr0;
    uint32_t addr1;
    uint32_t width;
    uint32_t height;
    uint32_t npb;
    uint32_t pixel_format;
    uint32_t sl;                // sl for interleaved mode, sly for non-interleaved mode
    uint32_t u_offset;          //uoffset
    uint32_t bpp;
    uint32_t so;
    uint32_t ilo;
    uint32_t bm;
    uint32_t rot;
    uint32_t hf;
    uint32_t vf;
} ipu_idmac_info_t;

typedef struct ipu_res_info {
    uint32_t addr0_in;
    uint32_t addr1_in;
    uint32_t addr0_out;
    uint32_t addr1_out;
    uint32_t width_in;
    uint32_t height_in;
    uint32_t width_out;
    uint32_t height_out;
    uint32_t strideline_in;     //sl for interleaved mode, sly for non-interleaved mode
    uint32_t strideline_out;
    uint32_t u_offset_in;
    uint32_t u_offset_out;
    uint32_t pixel_format_in;
    uint32_t pixel_format_out;
} ipu_res_info_t;

typedef struct ipu_vdi_info {
    uint32_t addr0_in;
    uint32_t addr1_in;
    uint32_t addr0_out;
    uint32_t addr1_out;
    uint32_t width_in;
    uint32_t height_in;
    uint32_t width_out;
    uint32_t height_out;
    uint32_t strideline_in;     //sl for interleaved mode, sly for non-interleaved mode
    uint32_t strideline_out;
    uint32_t u_offset_in;
    uint32_t u_offset_out;
    uint32_t pixel_format_in;
    uint32_t pixel_format_out;
    uint32_t field_mode;
    uint32_t motion_sel;
} ipu_vdi_info_t;

typedef struct ipu_rot_info {
    uint32_t addr0_in;
    uint32_t addr1_in;
    uint32_t addr0_out;
    uint32_t addr1_out;
    uint32_t width_in;
    uint32_t height_in;
    uint32_t width_out;
    uint32_t height_out;
    uint32_t strideline_in;
    uint32_t strideline_out;
    uint32_t ubo_in;
    uint32_t ubo_out;
    uint32_t pixel_format_in;
    uint32_t pixel_format_out;
    uint32_t rot;
    uint32_t hf;
    uint32_t vf;
} ipu_rot_info_t;

typedef struct alpha_chan_params {
    uint32_t alphaChanBaseAddr;
    int32_t alphaWidth;
    int32_t alphaHeight;
    int32_t alphaStrideline;
} alpha_chan_params_t;

typedef struct ic_comb_params {
    int32_t taskType;
    uint32_t baseAddr;
    int32_t width;
    int32_t height;
    int32_t alpha;
    int32_t inDataformat;
    alpha_chan_params_t alphaChan;
} ic_comb_params_t;

typedef struct ic_csc_params {
    int32_t taskType;
    int32_t inFormat;
    int32_t outFormat;
} ic_csc_params_t;

typedef struct ipu_task_params {
    int32_t taskType;
    int32_t resEnable;
    int32_t rotEnable;
    ipu_res_info_t resInfo;
    ipu_rot_info_t rotInfo;
} ipu_task_params_t;

typedef struct dp_fg_param {
    int32_t fgEnable;
    int32_t opaque;
    int32_t offsetVert;
    int32_t offsetHoriz;
    int32_t cursorEnable;
    int32_t colorKeyEnable;
    int32_t graphicSelect;
    int32_t alphaMode;
} dp_fg_param_t;

typedef struct di_sync_wave_gen {
    int32_t runValue;
    int32_t runResolution;
    int32_t offsetValue;
    int32_t offsetResolution;
    int32_t cntAutoReload;
    int32_t stepRepeat;
    int32_t cntClrSel;
    int32_t cntPolarityGenEn;
    int32_t cntPolarityTrigSel;
    int32_t cntPolarityClrSel;
    int32_t cntUp;
    int32_t cntDown;
} di_sync_wave_gen_t;

typedef struct di_cntl_signal {
    int32_t vsync_sel;
    int32_t vsync_pol;
    int32_t hsync_sel;
    int32_t hsync_pol;
    int32_t clk_sel;
    int32_t clk_pol;
    int32_t drdy_pol;
} di_cntl_signal_t;

#define GET_LSB(bit, val)  (((uint32_t)(val)) & ((0x1<<(bit)) - 1))

typedef struct dp_csc_param {
    int32_t mode;
    int32_t **coeff;
} dp_csc_param_t;

typedef struct ipu_hw_ic {
    int32_t pp_task;
    int32_t prp_enc_task;
    int32_t prp_vf_task;
} ipu_hw_ic_t;

typedef struct ipu_hw_di {
    int32_t dp_path_di0;
    int32_t dp_path_di1;
    int32_t dc_path_di0;
    int32_t dc_path_di1;
} ipu_hw_di_t;

typedef struct ipu_hw_resource {
    ipu_hw_ic_t ic;
    ipu_hw_di_t di;
} ipu_hw_resource_t;

int32_t ipu_sw_reset(int32_t ipu_index, int32_t timeout);
void ipu_disable_display(int32_t ipu_index);
void ipu_enable_display(int32_t ipu_index);
void ipu_display_setup(uint32_t ipu_index, uint32_t mem_addr0, uint32_t mem_addr1,
                       uint32_t mem_colorimetry, ips_dev_panel_t * panel);
void ipu_dual_display_setup(uint32_t ipu_index, ips_dev_panel_t * panel, uint32_t mem_colorimetry,
                            uint32_t fg_width, uint32_t fg_height, uint32_t fp_xp, uint32_t fp_yp,
                            uint32_t alpha);
void ipu_capture_setup(uint32_t ipu_index, uint32_t csi_interface, uint32_t raw_width,
                       uint32_t raw_height, uint32_t act_width, uint32_t act_height,
                       ips_dev_panel_t * panel);
void ipu_capture_streamoff(uint32_t ipu_index);

void ipu_mipi_csi2_setup(uint32_t ipu_index, uint32_t csi_width, uint32_t csi_height,
                         ips_dev_panel_t * panel);

inline void ipu_cpmem_set_field(uint32_t base, int32_t w, int32_t bit, int32_t size, uint32_t v);
void ipu_general_idmac_config(uint32_t ipu_index, ipu_idmac_info_t * idmac_info);
void ipu_disp_bg_idmac_config(uint32_t ipu_index, uint32_t addr0, uint32_t addr1, uint32_t width,
                              uint32_t height, uint32_t pixel_format);
void ipu_disp_fg_idmac_config(uint32_t ipu_index, uint32_t addr0, uint32_t addr1, uint32_t width,
                              uint32_t height, uint32_t pixel_format);
void ipu_csi_capture_idmac_config(uint32_t ipu_index, uint32_t width, uint32_t height,
                                  uint32_t pixel_format);
void ipu_dualdisp_idmac_config(uint32_t ipu_index, uint32_t width, uint32_t height,
                               uint32_t pixel_format);
void ipu_singledisp_idmac_config(uint32_t ipu_index, uint32_t width, uint32_t height,
                                 uint32_t pixel_format);

void ipu_rotate_idmac_config(uint32_t ipu_index, uint32_t channel_in, uint32_t channel_out,
                             ipu_rot_info_t rot_info);
void ipu_resize_idmac_config(uint32_t ipu_index, uint32_t channel_in, uint32_t channel_out,
                             ipu_res_info_t res_info);
void ipu_deinterlace_idmac_config(uint32_t ipu_index, uint32_t channel_in, uint32_t channel_out,
                                  ipu_vdi_info_t res_info);
void ipu_idma_pixel_format_config(uint32_t ipu_index, uint32_t channel, uint32_t pixel_format,
                                  uint32_t so, uint32_t sl, uint32_t ubo);
int32_t ipu_idmac_channel_busy(int32_t ipu_index, int32_t channel);
void ipu_idmac_channel_enable(int32_t ipu_index, int32_t channel, int32_t enable);
void ipu_channel_buf_ready(int32_t ipu_index, int32_t channel, int32_t buf);
void ipu_cpmem_mod_field(uint32_t base, int32_t w, int32_t bit, int32_t size, uint32_t v);

void ipu_dmfc_config(uint32_t ipu_index, uint32_t channel);
void ipu_dmfc_alloc(uint32_t ipu_index, uint32_t channel, uint32_t size, uint32_t start_addr,
                    uint32_t burst);

void ipu_dc_config(uint32_t ipu_index, uint32_t channel, uint32_t di, uint32_t width,
                   uint32_t colorimetry);
void ipu_dc_microcode_config(int32_t ipu_index, dc_microcode_t microcode);
void ipu_dc_microcode_event(int32_t ipu_index, int32_t channel, int32_t event, int32_t priority,
                            int32_t address);
int32_t ipu_dc_write_channel_config(int32_t ipu_index, int32_t dma_channel, int32_t disp_port,
                                    int32_t link_di_index, int32_t field_mode_enable);
int32_t ipu_dc_display_config(int32_t ipu_index, int32_t display_port, int32_t type,
                              int32_t increment, int32_t strideline);
int32_t ipu_dc_map(int32_t ipu_index, int32_t map, int32_t format);
void microcode_event(int32_t ipu_index, char channel[1], char event[8], int32_t priority,
                     int32_t address);

void ipu_dp_fg_config(uint32_t ipu_index, uint32_t dual_disp, uint32_t fg_xp, uint32_t fg_yp,
                      uint32_t alpha);
void ipu_dp_csc_config(uint32_t ipu_index, uint32_t dp, uint32_t csc_type);
void ipu_dp_config(uint32_t ipu_index, uint32_t csc_type, uint32_t dual_disp, uint32_t fg_xp,
                   uint32_t fg_yp, uint32_t alpha);

void ipu_di_config(uint32_t ipu_index, uint32_t di, ips_dev_panel_t * panel);
void ipu_di_waveform_config(int32_t ipu_index, int32_t di, int32_t pointer, int32_t set, int32_t up,
                            int32_t down);
int32_t ipu_di_screen_set(int32_t ipu_index, int32_t di, int32_t screen_height);
void ipu_di_pointer_config(int32_t ipu_index, int32_t di, int32_t pointer, int32_t access,
                           int32_t component, int32_t cst, int32_t * pt);
int32_t ipu_di_bsclk_gen(int32_t ipu_index, int32_t di, int32_t division, int32_t up, int32_t down);
void ipu_di_sync_config(int32_t ipu_index, int32_t di, int32_t pointer,
                        di_sync_wave_gen_t sync_waveform_gen);
void ipu_di_interface_set(uint32_t ipu_index, uint32_t di, ips_dev_panel_t * panel,
                          uint32_t line_prediction, uint32_t vsync_sel, uint32_t hsync_sel);

void ipu_ic_rotation_config(int32_t ipu_index, int32_t taskType, int32_t rot, int32_t hf,
                            int32_t vf);
void ipu_ic_resize_config(int32_t ipu_index, int32_t taskType, ipu_res_info_t res_info);
void ipu_ic_deinterlace_config(int32_t ipu_index, ipu_vdi_info_t vdi_info);
void ipu_ic_enable(int32_t ipu_index, int32_t ic_enable, int32_t irt_enable);
int32_t ipu_ic_calc_resize_coeffs(int32_t in_size, int32_t out_size, int32_t * resize_coeff,
                                  int32_t * downsize_coeff);
int32_t ipu_ic_config_resize_rate(int32_t ipu_index, char *task_type, uint32_t res_vert,
                                  uint32_t down_vert, uint32_t res_horiz, uint32_t down_horiz);
int32_t ipu_ic_combine_config(int32_t ipu_index, ic_comb_params_t comb_params);
int32_t ipu_ic_csc_config(int32_t ipu_index, int32_t csc_set_index, ic_csc_params_t csc_params);
int32_t ipu_ic_task_enable(int32_t ipu_index, int32_t task_type, int32_t task, int32_t enable);

void ipu_write_field(int32_t ipu_index, uint32_t ID_addr, uint32_t ID_mask, uint32_t data);
void ipu_write(int32_t ipu_index, uint32_t ID_addr, uint32_t data);
uint32_t ipu_read(int32_t ipu_index, uint32_t ID_addr);

void ipu_csi_config(uint32_t ipu_index, uint32_t csi_interface, uint32_t raw_width,
                    uint32_t raw_height, uint32_t act_width, uint32_t act_height);
uint32_t ipu_smfc_fifo_allocate(uint32_t ipu_index, uint32_t channel, uint32_t map,
                                uint32_t burst_size);
void ipu_capture_disp_link(uint32_t ipu_index, uint32_t smfc);
void ipu_disable_csi(uint32_t ipu_index, uint32_t csi);
void ipu_disable_smfc(uint32_t ipu_index);
void ipu_csi_test_mode_color(uint32_t ipu_index, int32_t color_mode);

ips_dev_panel_t *search_panel(char *panel_name);
ips_dev_panel_t *get_panel_by_id(uint32_t panel_id);
void list_panel(uint32_t panel_type);
void load_centralized_image(uint32_t addr, ips_dev_panel_t * panel);
void load_foreground_image(uint32_t addr, uint32_t width, uint32_t height);
void set_background_margin(ips_dev_panel_t * panel, uint32_t width, uint32_t height);

void load_horiz_image(uint32_t addr, uint32_t width, uint32_t height);
void ipu_dma_update_buffer(uint32_t ipu_index, uint32_t channel, uint32_t buffer_index,
                           uint32_t buffer_addr);
void ipu_vdi_init(int ipu_index, int fmt, int field_mode, int width, int height,
                  ips_motion_sel_e motion_sel);

extern int csi_vdi_direct_path;
extern ips_dev_panel_t disp_dev_list[];
extern uint32_t num_of_panels;

#endif
