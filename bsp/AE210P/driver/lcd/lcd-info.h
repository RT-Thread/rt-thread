#ifndef __LCD_INFO_H__
#define __LCD_INFO_H__

/*
 * HBP : Horizontal Back Porch
 * HFP : Horizontal Front Porch
 * HSPW: Horizontal Sync. Pulse Width
 * PPL : Pixels-per-line = 16(PPL+1)
 */
#define ENC_PARAM_TIME0(HBP, HFP, HSPW, PPL)	\
	((((HBP)         - 1) << 24) |		\
	 (((HFP)         - 1) << 16) |		\
	 (((HSPW)        - 1) << 8 ) |		\
	 ((((PPL) >> 4) - 1) << 2 ))

/*
 * HBP : Vertical Back Porch
 * HFP : Vertical Front Porch
 * HSPW: Vertical Sync. Pulse Width
 * LPP : Lines-per-panel = LPP + 1
 */
#define ENC_PARAM_TIME1(VBP, VFP, VSPW, LPP)	\
	((((VBP)     ) << 24) |			\
	 (((VFP)     ) << 16) |			\
	 (((VSPW) - 1) << 10) |			\
	 (((LPP)  - 1) ))

/*
 * PRA : Pixel Rate Adaptive
 * IOE : Invert Panel Output Enable
 * IPC : Invert Panel Clock (Test Chip Testing)
 * IHS : Invert Horisontal Sync.
 * IVS : Invert Versical Sync.
 * PCD : Panel Clock Divisor
 */
#define ENC_PARAM_TIME2(PRA, IOE, IPC, IHS, IVS, PCD)	\
	(((PRA)     << 15) |				\
	 ((IOE)     << 14) |				\
	 ((IPC)     << 13) |				\
	 ((IHS)     << 12) |				\
	 ((IVS)     << 11) |				\
	 (((PCD) - 1) ))

/*
 * Enable YCbCr
 * Enable YCbCr422
 * FIFO threadhold
 * Panel type, 0-6bit, 1-8bit
 * LcdVComp, when to generate interrupt, 1: start of back_porch
 * Power Enable
 * Big Endian Pixel/Byte Ordering
 * BGR
 * TFT
 * LCD bits per pixel
 * Controller Enable
 */
#define ENC_PARAM_CTRL(ENYUV, ENYUV422, FIFOTH, PTYPE, VCOMP, LCD_ON, ENDIAN, BGR, TFT, BPP, LCD_EN) \
	((ENYUV        << 18) |			\
	 (ENYUV422     << 17) |			\
	 (FIFOTH       << 16) |			\
	 (PTYPE        << 15) |			\
	 (VCOMP        << 12) |			\
	 (LCD_ON       << 11) |			\
	 (ENDIAN       <<  9) |			\
	 (BGR          <<  8) |			\
	 (TFT          <<  5) |			\
	 (BPP          <<  1) |			\
	 (LCD_EN))

#if defined(CONFIG_COLOR_DEPTH16)
#define LCD_COLOR_DEPTH		0x4
#define LCD_PANEL_BPP		16
#elif defined(CONFIG_COLOR_DEPTH24)
#define LCD_COLOR_DEPTH		0x5
#define LCD_PANEL_BPP		24
#else
#define LCD_COLOR_DEPTH		0x5
#define LCD_PANEL_BPP		24
#endif

#ifdef CONFIG_PANEL_AUA036QN01

#define LCD_PANEL_WIDTH		320
#define LCD_PANEL_HEIGHT	240

#define LCD_TIME0		ENC_PARAM_TIME0(7, 6, 1, 320) /* 0x0605004c */
#define LCD_TIME1		ENC_PARAM_TIME1(1, 1, 1, 240) /* 0x010100ef */
#define LCD_TIME2		ENC_PARAM_TIME2(0, 0, 1, 1, 1, 0x7) /* 0x00003806 */
#define LCD_CTRL		ENC_PARAM_CTRL(0, 0, 1, 1, 0x3, 1, 0x0, 1, 1, LCD_COLOR_DEPTH, 1) /* 0x0001b928 */

#endif

#ifdef CONFIG_PANEL_AUA070VW04

#define LCD_PANEL_WIDTH		800
#define LCD_PANEL_HEIGHT	480

#define LCD_TIME0		ENC_PARAM_TIME0(88, 40, 128, 800)
#define LCD_TIME1		ENC_PARAM_TIME1(21, 1, 3, 480)
#define LCD_TIME2		ENC_PARAM_TIME2(0, 1, 1, 1, 1, 0x7)
#define LCD_CTRL		ENC_PARAM_CTRL(0, 0, 1, 1, 0x3, 1, 0x0, 1, 1, LCD_COLOR_DEPTH, 1)

#endif

#ifdef CONFIG_PANEL_CH7013A

#define LCD_TIME0		ENC_PARAM_TIME0(42, 10, 96, 640)
#define LCD_TIME1		ENC_PARAM_TIME1(28, 5, 2, 480)
#define LCD_TIME2		ENC_PARAM_TIME2(0, 1, 1, 0, 0, 0x3)
#define LCD_CTRL		ENC_PARAM_CTRL(0, 0, 1, 0, 0x3, 1, 0x0, 1, 1, LCD_COLOR_DEPTH, 1)

#endif /* CONFIG_CH7013A */

#endif /* __LCD_INFO_H__ */
