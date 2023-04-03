/* g2d_driver.h
 *
 * Copyright (c)	2011 xxxx Electronics
 *					2011 Yupu Tang
 *
 * @ F23 G2D driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 */

#ifndef __G2D_DRIVER_H
#define __G2D_DRIVER_H
#include <typedef.h>
#include <errno.h>



/* data format */
typedef enum {
	G2D_FORMAT_ARGB8888,
	G2D_FORMAT_ABGR8888,
	G2D_FORMAT_RGBA8888,
	G2D_FORMAT_BGRA8888,
	G2D_FORMAT_XRGB8888,
	G2D_FORMAT_XBGR8888,
	G2D_FORMAT_RGBX8888,
	G2D_FORMAT_BGRX8888,
	G2D_FORMAT_RGB888,
	G2D_FORMAT_BGR888,
	G2D_FORMAT_RGB565,
	G2D_FORMAT_BGR565,
	G2D_FORMAT_ARGB4444,
	G2D_FORMAT_ABGR4444,
	G2D_FORMAT_RGBA4444,
	G2D_FORMAT_BGRA4444,
	G2D_FORMAT_ARGB1555,
	G2D_FORMAT_ABGR1555,
	G2D_FORMAT_RGBA5551,
	G2D_FORMAT_BGRA5551,
	G2D_FORMAT_ARGB2101010,
	G2D_FORMAT_ABGR2101010,
	G2D_FORMAT_RGBA1010102,
	G2D_FORMAT_BGRA1010102,

	/* invailed for UI channel */
	G2D_FORMAT_IYUV422_V0Y1U0Y0 = 0x20,
	G2D_FORMAT_IYUV422_Y1V0Y0U0,
	G2D_FORMAT_IYUV422_U0Y1V0Y0,
	G2D_FORMAT_IYUV422_Y1U0Y0V0,

	G2D_FORMAT_YUV422UVC_V1U1V0U0,
	G2D_FORMAT_YUV422UVC_U1V1U0V0,
	G2D_FORMAT_YUV422_PLANAR,

	G2D_FORMAT_YUV420UVC_V1U1V0U0 = 0x28,
	G2D_FORMAT_YUV420UVC_U1V1U0V0,
	G2D_FORMAT_YUV420_PLANAR,

	G2D_FORMAT_YUV411UVC_V1U1V0U0 = 0x2c,
	G2D_FORMAT_YUV411UVC_U1V1U0V0,
	G2D_FORMAT_YUV411_PLANAR,

	G2D_FORMAT_Y8 = 0x30,

	/* YUV 10bit format */
	G2D_FORMAT_YVU10_P010 = 0x34,

	G2D_FORMAT_YVU10_P210 = 0x36,

	G2D_FORMAT_YVU10_444 = 0x38,
	G2D_FORMAT_YUV10_444 = 0x39,
	G2D_FORMAT_MAX,
} g2d_fmt_enh;
/* mixer data format */
typedef enum {
	/* share data format */
	G2D_FMT_ARGB_AYUV8888	= (0x0),
	G2D_FMT_BGRA_VUYA8888	= (0x1),
	G2D_FMT_ABGR_AVUY8888	= (0x2),
	G2D_FMT_RGBA_YUVA8888	= (0x3),

	G2D_FMT_XRGB8888		= (0x4),
	G2D_FMT_BGRX8888		= (0x5),
	G2D_FMT_XBGR8888		= (0x6),
	G2D_FMT_RGBX8888		= (0x7),

	G2D_FMT_ARGB4444		= (0x8),
	G2D_FMT_ABGR4444		= (0x9),
	G2D_FMT_RGBA4444		= (0xA),
	G2D_FMT_BGRA4444		= (0xB),

	G2D_FMT_ARGB1555		= (0xC),
	G2D_FMT_ABGR1555		= (0xD),
	G2D_FMT_RGBA5551		= (0xE),
	G2D_FMT_BGRA5551		= (0xF),

	G2D_FMT_RGB565			= (0x10),
	G2D_FMT_BGR565			= (0x11),

	G2D_FMT_IYUV422			= (0x12),

	G2D_FMT_8BPP_MONO		= (0x13),
	G2D_FMT_4BPP_MONO		= (0x14),
	G2D_FMT_2BPP_MONO		= (0x15),
	G2D_FMT_1BPP_MONO		= (0x16),

	G2D_FMT_PYUV422UVC		= (0x17),
	G2D_FMT_PYUV420UVC		= (0x18),
	G2D_FMT_PYUV411UVC		= (0x19),

	/* just for output format */
	G2D_FMT_PYUV422			= (0x1A),
	G2D_FMT_PYUV420			= (0x1B),
	G2D_FMT_PYUV411			= (0x1C),

	/* just for input format */
	G2D_FMT_8BPP_PALETTE	= (0x1D),
	G2D_FMT_4BPP_PALETTE	= (0x1E),
	G2D_FMT_2BPP_PALETTE	= (0x1F),
	G2D_FMT_1BPP_PALETTE	= (0x20),

	G2D_FMT_PYUV422UVC_MB16	= (0x21),
	G2D_FMT_PYUV420UVC_MB16	= (0x22),
	G2D_FMT_PYUV411UVC_MB16	= (0x23),
	G2D_FMT_PYUV422UVC_MB32	= (0x24),
	G2D_FMT_PYUV420UVC_MB32	= (0x25),
	G2D_FMT_PYUV411UVC_MB32	= (0x26),
	G2D_FMT_PYUV422UVC_MB64	= (0x27),
	G2D_FMT_PYUV420UVC_MB64	= (0x28),
	G2D_FMT_PYUV411UVC_MB64	= (0x29),
	G2D_FMT_PYUV422UVC_MB128 = (0x2A),
	G2D_FMT_PYUV420UVC_MB128 = (0x2B),
	G2D_FMT_PYUV411UVC_MB128 = (0x2C),

} g2d_data_fmt;

/* pixel sequence in double word */
typedef enum {
	G2D_SEQ_NORMAL = 0x0,

	/* for interleaved yuv422 */
	G2D_SEQ_VYUY   = 0x1,			/* pixel 0在16位 */
	G2D_SEQ_YVYU   = 0x2,			/* pixel 1在16位 */

	/* for uv_combined yuv420 */
	G2D_SEQ_VUVU   = 0x3,

	/* for 16bpp rgb */
	G2D_SEQ_P10    = 0x4,			/* pixel 0在16位 */
	G2D_SEQ_P01    = 0x5,			/* pixel 1在16位 */

	/* planar format or 8bpp rgb */
	G2D_SEQ_P3210  = 0x6,			/* pixel 0在8位 */
	G2D_SEQ_P0123  = 0x7,			/* pixel 3在8位 */

	/* for 4bpp rgb */
	G2D_SEQ_P76543210  = 0x8,			/* 7,6,5,4,3,2,1,0 */
	G2D_SEQ_P67452301  = 0x9,			/* 6,7,4,5,2,3,0,1 */
	G2D_SEQ_P10325476  = 0xA,			/* 1,0,3,2,5,4,7,6 */
	G2D_SEQ_P01234567  = 0xB,			/* 0,1,2,3,4,5,6,7 */

	/* for 2bpp rgb */
	/* 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 */
	G2D_SEQ_2BPP_BIG_BIG       = 0xC,
	/* 12,13,14,15,8,9,10,11,4,5,6,7,0,1,2,3 */
	G2D_SEQ_2BPP_BIG_LITTER    = 0xD,
	/* 3,2,1,0,7,6,5,4,11,10,9,8,15,14,13,12 */
	G2D_SEQ_2BPP_LITTER_BIG    = 0xE,
	/* 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 */
	G2D_SEQ_2BPP_LITTER_LITTER = 0xF,

	/* for 1bpp rgb */
	/* 31,30,29,28,27,26,25,24,23,22,21,20,
	 * 19,18,17,16,15,14,13,12,11,10,9,8,7,
	 * 6,5,4,3,2,1,0
	 */
	G2D_SEQ_1BPP_BIG_BIG       = 0x10,
	/* 24,25,26,27,28,29,30,31,16,17,
	 * 18,19,20,21,22,23,8,9,10,11,12,
	 * 13,14,15,0,1,2,3,4,5,6,7
	 */
	G2D_SEQ_1BPP_BIG_LITTER    = 0x11,
	/* 7,6,5,4,3,2,1,0,15,14,13,12,11,
	 * 10,9,8,23,22,21,20,19,18,17,16,
	 * 31,30,29,28,27,26,25,24
	 */
	G2D_SEQ_1BPP_LITTER_BIG    = 0x12,
	/* 0,1,2,3,4,5,6,7,8,9,10,11,12,13,
	 * 14,15,16,17,18,19,20,21,22,23,24,
	 * 25,26,27,28,29,30,31
	 */
	G2D_SEQ_1BPP_LITTER_LITTER = 0x13,
} g2d_pixel_seq;

/*  */
typedef enum {
	G2D_BLT_NONE_H = 0x0,
	G2D_BLT_BLACKNESS,
	G2D_BLT_NOTMERGEPEN,
	G2D_BLT_MASKNOTPEN,
	G2D_BLT_NOTCOPYPEN,
	G2D_BLT_MASKPENNOT,
	G2D_BLT_NOT,
	G2D_BLT_XORPEN,
	G2D_BLT_NOTMASKPEN,
	G2D_BLT_MASKPEN,
	G2D_BLT_NOTXORPEN,
	G2D_BLT_NOP,
	G2D_BLT_MERGENOTPEN,
	G2D_BLT_COPYPEN,
	G2D_BLT_MERGEPENNOT,
	G2D_BLT_MERGEPEN,
	G2D_BLT_WHITENESS = 0x000000ff,

	G2D_ROT_90  = 0x00000100,
	G2D_ROT_180 = 0x00000200,
	G2D_ROT_270 = 0x00000300,
	G2D_ROT_0   = 0x00000400,
	G2D_ROT_H = 0x00001000,
	G2D_ROT_V = 0x00002000,

/*	G2D_SM_TDLR_1  =    0x10000000, */
	G2D_SM_DTLR_1 = 0x10000000,
/*	G2D_SM_TDRL_1  =    0x20000000, */
/*	G2D_SM_DTRL_1  =    0x30000000, */
} g2d_blt_flags_h;

/* ROP3 command */
typedef enum {
	G2D_ROP3_BLACKNESS = 0x00,
	G2D_ROP3_NOTSRCERASE = 0x11,
	G2D_ROP3_NOTSRCCOPY = 0x33,
	G2D_ROP3_SRCERASE = 0x44,
	G2D_ROP3_DSTINVERT = 0x55,
	G2D_ROP3_PATINVERT = 0x5A,
	G2D_ROP3_SRCINVERT = 0x66,
	G2D_ROP3_SRCAND = 0x88,
	G2D_ROP3_MERGEPAINT = 0xBB,
	G2D_ROP3_MERGECOPY = 0xC0,
	G2D_ROP3_SRCCOPY = 0xCC,
	G2D_ROP3_SRCPAINT = 0xEE,
	G2D_ROP3_PATCOPY = 0xF0,
	G2D_ROP3_PATPAINT = 0xFB,
	G2D_ROP3_WHITENESS = 0xFF,
} g2d_rop3_cmd_flag;

typedef enum {
	G2D_FIL_NONE			= 0x00000000,
	G2D_FIL_PIXEL_ALPHA		= 0x00000001,
	G2D_FIL_PLANE_ALPHA		= 0x00000002,
	G2D_FIL_MULTI_ALPHA		= 0x00000004,
} g2d_fillrect_flags;

typedef enum {
	G2D_BLT_NONE			= 0x00000000,
	G2D_BLT_PIXEL_ALPHA		= 0x00000001,
	G2D_BLT_PLANE_ALPHA		= 0x00000002,
	G2D_BLT_MULTI_ALPHA		= 0x00000004,
	G2D_BLT_SRC_COLORKEY	= 0x00000008,
	G2D_BLT_DST_COLORKEY	= 0x00000010,
	G2D_BLT_FLIP_HORIZONTAL	= 0x00000020,
	G2D_BLT_FLIP_VERTICAL	= 0x00000040,
	G2D_BLT_ROTATE90		= 0x00000080,
	G2D_BLT_ROTATE180		= 0x00000100,
	G2D_BLT_ROTATE270		= 0x00000200,
	G2D_BLT_MIRROR45		= 0x00000400,
	G2D_BLT_MIRROR135		= 0x00000800,
	G2D_BLT_SRC_PREMULTIPLY	= 0x00001000,
	G2D_BLT_DST_PREMULTIPLY	= 0x00002000,
} g2d_blt_flags;

/* BLD LAYER ALPHA MODE*/
typedef enum {
	G2D_PIXEL_ALPHA,
	G2D_GLOBAL_ALPHA,
	G2D_MIXER_ALPHA,
} g2d_alpha_mode_enh;

/* flip rectangle struct */
typedef struct {
	__s32		x;		/* left top point coordinate x */
	__s32		y;		/* left top point coordinate y */
	__u32		w;		/* rectangle width */
	__u32		h;		/* rectangle height */
} g2d_rect;

/* g2d color gamut */
typedef enum {
	G2D_BT601,
	G2D_BT709,
	G2D_BT2020,
} g2d_color_gmt;

/* image struct */
typedef struct {
	__u32		addr[3];/* base addr of image frame buffer in byte */
	__u32		w;	/* width of image frame buffer in pixel */
	__u32		h;	/* height of image frame buffer in pixel */
	g2d_data_fmt	format;	/* pixel format of image frame buffer */
	g2d_pixel_seq	pixel_seq;/* pixel sequence of image frame buffer */
} g2d_image;

typedef struct {
	/* left point coordinate x of dst rect */
	unsigned int x;
	/* top point coordinate y of dst rect */
	unsigned int y;
} g2d_coor;

/* image struct */
typedef struct {
	int		 bbuff;
	__u32		 color;
	g2d_fmt_enh	 format;
	__u32		 laddr[3];
	__u32		 haddr[3];
	__u32		 width;
	__u32		 height;
	__u32		 align[3];

	g2d_rect	 clip_rect;
	g2d_coor	 coor;

	__u32		 gamut;
	int		 bpremul;
	__u8		 alpha;
	g2d_alpha_mode_enh mode;
	int		 fd;
	__u32 use_phy_addr;
} g2d_image_enh;

/*
 * 0:Top to down, Left to right
 * 1:Top to down, Right to left
 * 2:Down to top, Left to right
 * 3:Down to top, Right to left
 */
enum g2d_scan_order {
	G2D_SM_TDLR = 0x00000000,
	G2D_SM_TDRL = 0x00000001,
	G2D_SM_DTLR = 0x00000002,
	G2D_SM_DTRL = 0x00000003,
};

typedef struct {
	g2d_fillrect_flags	 flag;
	g2d_image			 dst_image;
	g2d_rect			 dst_rect;

	__u32				 color;		/* fill color */
	__u32				 alpha;		/* plane alpha value */

} g2d_fillrect;

typedef struct {
	g2d_image_enh dst_image_h;
} g2d_fillrect_h;

typedef struct {
	g2d_blt_flags		flag;
	g2d_image		src_image;
	g2d_rect		src_rect;

	g2d_image		dst_image;
	/* left top point coordinate x of dst rect */
	__s32			dst_x;
	/* left top point coordinate y of dst rect */
	__s32			dst_y;

	__u32			color;		/* colorkey color */
	__u32			alpha;		/* plane alpha value */

} g2d_blt;

typedef struct {
	g2d_blt_flags_h flag_h;
	g2d_image_enh src_image_h;
	g2d_image_enh dst_image_h;
} g2d_blt_h;

typedef struct {
	g2d_blt_h blt;
	__u32	lbc_cmp_ratio;
	__u8	enc_is_lossy;
	__u8	dec_is_lossy;
} g2d_lbc_rot;
typedef struct {
	g2d_blt_flags			 flag;
	g2d_image			 src_image;
	g2d_rect			 src_rect;

	g2d_image			 dst_image;
	g2d_rect			 dst_rect;

	__u32				 color;		/* colorkey color */
	__u32				 alpha;		/* plane alpha value */


} g2d_stretchblt;

typedef struct {
	g2d_rop3_cmd_flag back_flag;
	g2d_rop3_cmd_flag fore_flag;

	g2d_image_enh dst_image_h;
	g2d_image_enh src_image_h;
	g2d_image_enh ptn_image_h;
	g2d_image_enh mask_image_h;

} g2d_maskblt;

/* Porter Duff BLD command*/
typedef enum {
	G2D_BLD_CLEAR = 0x00000001,
	G2D_BLD_COPY = 0x00000002,
	G2D_BLD_DST = 0x00000003,
	G2D_BLD_SRCOVER = 0x00000004,
	G2D_BLD_DSTOVER = 0x00000005,
	G2D_BLD_SRCIN = 0x00000006,
	G2D_BLD_DSTIN = 0x00000007,
	G2D_BLD_SRCOUT = 0x00000008,
	G2D_BLD_DSTOUT = 0x00000009,
	G2D_BLD_SRCATOP = 0x0000000a,
	G2D_BLD_DSTATOP = 0x0000000b,
	G2D_BLD_XOR = 0x0000000c,
	G2D_CK_SRC = 0x00010000,
	G2D_CK_DST = 0x00020000,
} g2d_bld_cmd_flag;

typedef struct {
	__u32		*pbuffer;
	__u32		 size;

} g2d_palette;



typedef struct {
	long	start;
	long	end;
} g2d_cache_range;

/* CK PARA struct */
typedef struct {
	int match_rule;
	__u32 max_color;
	__u32 min_color;
} g2d_ck;

typedef struct {
	g2d_bld_cmd_flag bld_cmd;
	g2d_image_enh dst_image;
	g2d_image_enh src_image[4];/*now only ch0 and ch3*/
	g2d_ck ck_para;
} g2d_bld;			/* blending enhance */

typedef enum {
	OP_FILLRECT = 0x1,
	OP_BITBLT = 0x2,
	OP_BLEND = 0x4,
	OP_MASK = 0x8,
	OP_SPLIT_MEM = 0x10,
} g2d_operation_flag;

/**
 * mixer_para
 */
struct mixer_para {
	g2d_operation_flag op_flag;
	g2d_blt_flags_h flag_h;
	g2d_rop3_cmd_flag back_flag;
	g2d_rop3_cmd_flag fore_flag;
	g2d_bld_cmd_flag bld_cmd;
	g2d_image_enh src_image_h;
	g2d_image_enh dst_image_h;
	g2d_image_enh ptn_image_h;
	g2d_image_enh mask_image_h;
	g2d_ck ck_para;
};
/*
#define SUNXI_G2D_IOC_MAGIC 'G'
#define SUNXI_G2D_IO(nr)          _IO(SUNXI_G2D_IOC_MAGIC, nr)
#define SUNXI_G2D_IOR(nr, size)   _IOR(SUNXI_G2D_IOC_MAGIC, nr, size)
#define SUNXI_G2D_IOW(nr, size)   _IOW(SUNXI_G2D_IOC_MAGIC, nr, size)
#define SUNXI_G2D_IOWR(nr, size)  _IOWR(SUNXI_G2D_IOC_MAGIC, nr, size)
*/
typedef enum {
	G2D_CMD_BITBLT			=	0x50,
	G2D_CMD_FILLRECT		=	0x51,
	G2D_CMD_STRETCHBLT		=	0x52,
	G2D_CMD_PALETTE_TBL		=	0x53,
	G2D_CMD_QUEUE			=	0x54,
	G2D_CMD_BITBLT_H		=	0x55,
	G2D_CMD_FILLRECT_H		=	0x56,
	G2D_CMD_BLD_H			=	0x57,
	G2D_CMD_MASK_H			=	0x58,

	G2D_CMD_MEM_REQUEST		=	0x59,
	G2D_CMD_MEM_RELEASE		=	0x5A,
	G2D_CMD_MEM_GETADR		=	0x5B,
	G2D_CMD_MEM_SELIDX		=	0x5C,
	G2D_CMD_MEM_FLUSH_CACHE		=	0x5D,
	G2D_CMD_INVERTED_ORDER		=	0x5E,
	G2D_CMD_MIXER_TASK		=	0x5F,
	/*G2D_CMD_CREATE_TASK = SUNXI_G2D_IOW(0x1, struct mixer_para),
	G2D_CMD_TASK_APPLY = SUNXI_G2D_IOW(0x2, struct mixer_para),
	G2D_CMD_TASK_DESTROY = SUNXI_G2D_IOW(0x3, unsigned int),
	G2D_CMD_TASK_GET_PARA = SUNXI_G2D_IOR(0x4, struct mixer_para),  */
	G2D_CMD_CREATE_TASK		=	0x60,
	G2D_CMD_TASK_APPLY		=	0x61,
	G2D_CMD_TASK_DESTROY		=	0x62,
	G2D_CMD_TASK_GET_PARA		=	0x63,
	G2D_CMD_LBC_ROT			=	0x64,

} g2d_cmd;

#endif	/* __G2D_DRIVER_H */

