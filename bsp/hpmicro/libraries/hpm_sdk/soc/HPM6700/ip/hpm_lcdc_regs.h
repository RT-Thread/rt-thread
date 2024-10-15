/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LCDC_H
#define HPM_LCDC_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: Control Register */
    __RW uint32_t BGND_CL;                     /* 0x4: Background Color Register */
    __RW uint32_t DISP_WN_SIZE;                /* 0x8: Display Window Size Register */
    __RW uint32_t HSYNC_PARA;                  /* 0xC: HSYNC Config Register */
    __RW uint32_t VSYNC_PARA;                  /* 0x10: VSYNC Config Register */
    __W  uint32_t DMA_ST;                      /* 0x14: DMA Status Register */
    __W  uint32_t ST;                          /* 0x18: Status Register */
    __RW uint32_t INT_EN;                      /* 0x1C: Interrupt Enable Register */
    __RW uint32_t TXFIFO;                      /* 0x20: TX FIFO Register */
    __R  uint8_t  RESERVED0[476];              /* 0x24 - 0x1FF: Reserved */
    struct {
        __RW uint32_t LAYCTRL;                 /* 0x200: Layer Control Register */
        __RW uint32_t ALPHAS;                  /* 0x204: Layer Alpha Register */
        __RW uint32_t LAYSIZE;                 /* 0x208: Layer Size Register */
        __RW uint32_t LAYPOS;                  /* 0x20C: Layer Position Register */
        __RW uint32_t START0;                  /* 0x210: Layer Buffer Pointer Register */
        __R  uint8_t  RESERVED0[4];            /* 0x214 - 0x217: Reserved */
        __RW uint32_t LINECFG;                 /* 0x218: Layer Bus Config Register */
        __RW uint32_t BG_CL;                   /* 0x21C: Layer Background Color Register */
        __RW uint32_t CSC_COEF0;               /* 0x220: Layer Color Space Conversion Config Register 0 */
        __RW uint32_t CSC_COEF1;               /* 0x224: Layer Color Space Conversion Config Register 1 */
        __RW uint32_t CSC_COEF2;               /* 0x228: Layer Color Space Conversion Config Register 2 */
        __R  uint8_t  RESERVED1[20];           /* 0x22C - 0x23F: Reserved */
    } LAYER[8];
    __RW uint32_t CLUT_LOAD;                   /* 0x400: Clut Load Control Register */
} LCDC_Type;


/* Bitfield definition for register: CTRL */
/*
 * SW_RST (RW)
 *
 * Software reset, high active. When write 1 ,all internal logical will be reset.
 * 0b - No action
 * 1b - All LCDC internal registers are forced into their reset state. Interface registers are not affected.
 */
#define LCDC_CTRL_SW_RST_MASK (0x80000000UL)
#define LCDC_CTRL_SW_RST_SHIFT (31U)
#define LCDC_CTRL_SW_RST_SET(x) (((uint32_t)(x) << LCDC_CTRL_SW_RST_SHIFT) & LCDC_CTRL_SW_RST_MASK)
#define LCDC_CTRL_SW_RST_GET(x) (((uint32_t)(x) & LCDC_CTRL_SW_RST_MASK) >> LCDC_CTRL_SW_RST_SHIFT)

/*
 * DISP_ON (RW)
 *
 * Display panel On/Off mode.
 * 0b - Display Off.
 * 1b - Display On.
 * Display can be set off at any time, but it can only be set on after VS_BLANK status is asserted.
 * So a good procedure to stop and turn on the display is:
 * 1) clr VS_BLANK status
 * 2) assert software reset
 * 3) de-assert software reset
 * 4) set display off
 * 5) check VS_BLANK status until it is asserted,
 * 6)reset the module, change settings
 * 7) set display on
 */
#define LCDC_CTRL_DISP_ON_MASK (0x40000000UL)
#define LCDC_CTRL_DISP_ON_SHIFT (30U)
#define LCDC_CTRL_DISP_ON_SET(x) (((uint32_t)(x) << LCDC_CTRL_DISP_ON_SHIFT) & LCDC_CTRL_DISP_ON_MASK)
#define LCDC_CTRL_DISP_ON_GET(x) (((uint32_t)(x) & LCDC_CTRL_DISP_ON_MASK) >> LCDC_CTRL_DISP_ON_SHIFT)

/*
 * LINE_PATTERN (RW)
 *
 * LCDIF line output order.
 * 000b - RGB.
 * 001b - RBG.
 * 010b - GBR.
 * 011b - GRB.
 * 100b - BRG.
 * 101b - BGR.
 */
#define LCDC_CTRL_LINE_PATTERN_MASK (0x38000000UL)
#define LCDC_CTRL_LINE_PATTERN_SHIFT (27U)
#define LCDC_CTRL_LINE_PATTERN_SET(x) (((uint32_t)(x) << LCDC_CTRL_LINE_PATTERN_SHIFT) & LCDC_CTRL_LINE_PATTERN_MASK)
#define LCDC_CTRL_LINE_PATTERN_GET(x) (((uint32_t)(x) & LCDC_CTRL_LINE_PATTERN_MASK) >> LCDC_CTRL_LINE_PATTERN_SHIFT)

/*
 * DISP_MODE (RW)
 *
 * LCDIF operating mode.
 * 00b - Normal mode. Panel content controlled by layer configuration.
 * 01b - Test Mode1.(BGND Color Display)
 * 10b - Test Mode2.(Column Color Bar)
 * 11b - Test Mode3.(Row Color Bar)
 */
#define LCDC_CTRL_DISP_MODE_MASK (0x6000000UL)
#define LCDC_CTRL_DISP_MODE_SHIFT (25U)
#define LCDC_CTRL_DISP_MODE_SET(x) (((uint32_t)(x) << LCDC_CTRL_DISP_MODE_SHIFT) & LCDC_CTRL_DISP_MODE_MASK)
#define LCDC_CTRL_DISP_MODE_GET(x) (((uint32_t)(x) & LCDC_CTRL_DISP_MODE_MASK) >> LCDC_CTRL_DISP_MODE_SHIFT)

/*
 * BGDCL4CLR (RW)
 *
 * background color for clear mode when the alpha channel is 0
 */
#define LCDC_CTRL_BGDCL4CLR_MASK (0x1000000UL)
#define LCDC_CTRL_BGDCL4CLR_SHIFT (24U)
#define LCDC_CTRL_BGDCL4CLR_SET(x) (((uint32_t)(x) << LCDC_CTRL_BGDCL4CLR_SHIFT) & LCDC_CTRL_BGDCL4CLR_MASK)
#define LCDC_CTRL_BGDCL4CLR_GET(x) (((uint32_t)(x) & LCDC_CTRL_BGDCL4CLR_MASK) >> LCDC_CTRL_BGDCL4CLR_SHIFT)

/*
 * ARQOS (RW)
 *
 * ARQOS for bus fabric arbitration
 */
#define LCDC_CTRL_ARQOS_MASK (0xF00000UL)
#define LCDC_CTRL_ARQOS_SHIFT (20U)
#define LCDC_CTRL_ARQOS_SET(x) (((uint32_t)(x) << LCDC_CTRL_ARQOS_SHIFT) & LCDC_CTRL_ARQOS_MASK)
#define LCDC_CTRL_ARQOS_GET(x) (((uint32_t)(x) & LCDC_CTRL_ARQOS_MASK) >> LCDC_CTRL_ARQOS_SHIFT)

/*
 * INV_PXDATA (RW)
 *
 * Indicates if value at the output (pixel data output) needs to be negated.
 * 0b - Output is to remain same as the data inside memory
 * 1b - Output to be negated from the data inside memory
 */
#define LCDC_CTRL_INV_PXDATA_MASK (0x10U)
#define LCDC_CTRL_INV_PXDATA_SHIFT (4U)
#define LCDC_CTRL_INV_PXDATA_SET(x) (((uint32_t)(x) << LCDC_CTRL_INV_PXDATA_SHIFT) & LCDC_CTRL_INV_PXDATA_MASK)
#define LCDC_CTRL_INV_PXDATA_GET(x) (((uint32_t)(x) & LCDC_CTRL_INV_PXDATA_MASK) >> LCDC_CTRL_INV_PXDATA_SHIFT)

/*
 * INV_PXCLK (RW)
 *
 * Polarity change of Pixel Clock.
 * 0b - LCDC outputs data on the rising edge, and Display samples data on the falling edge
 * 1b - LCDC outputs data on the falling edge, Display samples data on the rising edge
 */
#define LCDC_CTRL_INV_PXCLK_MASK (0x8U)
#define LCDC_CTRL_INV_PXCLK_SHIFT (3U)
#define LCDC_CTRL_INV_PXCLK_SET(x) (((uint32_t)(x) << LCDC_CTRL_INV_PXCLK_SHIFT) & LCDC_CTRL_INV_PXCLK_MASK)
#define LCDC_CTRL_INV_PXCLK_GET(x) (((uint32_t)(x) & LCDC_CTRL_INV_PXCLK_MASK) >> LCDC_CTRL_INV_PXCLK_SHIFT)

/*
 * INV_HREF (RW)
 *
 * Polarity of HREF
 * 0b - HREF signal active HIGH, indicating active pixel data
 * 1b - HREF signal active LOW
 */
#define LCDC_CTRL_INV_HREF_MASK (0x4U)
#define LCDC_CTRL_INV_HREF_SHIFT (2U)
#define LCDC_CTRL_INV_HREF_SET(x) (((uint32_t)(x) << LCDC_CTRL_INV_HREF_SHIFT) & LCDC_CTRL_INV_HREF_MASK)
#define LCDC_CTRL_INV_HREF_GET(x) (((uint32_t)(x) & LCDC_CTRL_INV_HREF_MASK) >> LCDC_CTRL_INV_HREF_SHIFT)

/*
 * INV_VSYNC (RW)
 *
 * Polarity of VSYNC
 * 0b - VSYNC signal active HIGH
 * 1b - VSYNC signal active LOW
 */
#define LCDC_CTRL_INV_VSYNC_MASK (0x2U)
#define LCDC_CTRL_INV_VSYNC_SHIFT (1U)
#define LCDC_CTRL_INV_VSYNC_SET(x) (((uint32_t)(x) << LCDC_CTRL_INV_VSYNC_SHIFT) & LCDC_CTRL_INV_VSYNC_MASK)
#define LCDC_CTRL_INV_VSYNC_GET(x) (((uint32_t)(x) & LCDC_CTRL_INV_VSYNC_MASK) >> LCDC_CTRL_INV_VSYNC_SHIFT)

/*
 * INV_HSYNC (RW)
 *
 * Polarity of HSYNC
 * 0b - HSYNC signal active HIGH
 * 1b - HSYNC signal active LOW
 */
#define LCDC_CTRL_INV_HSYNC_MASK (0x1U)
#define LCDC_CTRL_INV_HSYNC_SHIFT (0U)
#define LCDC_CTRL_INV_HSYNC_SET(x) (((uint32_t)(x) << LCDC_CTRL_INV_HSYNC_SHIFT) & LCDC_CTRL_INV_HSYNC_MASK)
#define LCDC_CTRL_INV_HSYNC_GET(x) (((uint32_t)(x) & LCDC_CTRL_INV_HSYNC_MASK) >> LCDC_CTRL_INV_HSYNC_SHIFT)

/* Bitfield definition for register: BGND_CL */
/*
 * R (RW)
 *
 * Red component of the default color displayed in the sectors where no layer is active.
 */
#define LCDC_BGND_CL_R_MASK (0xFF0000UL)
#define LCDC_BGND_CL_R_SHIFT (16U)
#define LCDC_BGND_CL_R_SET(x) (((uint32_t)(x) << LCDC_BGND_CL_R_SHIFT) & LCDC_BGND_CL_R_MASK)
#define LCDC_BGND_CL_R_GET(x) (((uint32_t)(x) & LCDC_BGND_CL_R_MASK) >> LCDC_BGND_CL_R_SHIFT)

/*
 * G (RW)
 *
 * Green component of the default color displayed in the sectors where no layer is active.
 */
#define LCDC_BGND_CL_G_MASK (0xFF00U)
#define LCDC_BGND_CL_G_SHIFT (8U)
#define LCDC_BGND_CL_G_SET(x) (((uint32_t)(x) << LCDC_BGND_CL_G_SHIFT) & LCDC_BGND_CL_G_MASK)
#define LCDC_BGND_CL_G_GET(x) (((uint32_t)(x) & LCDC_BGND_CL_G_MASK) >> LCDC_BGND_CL_G_SHIFT)

/*
 * B (RW)
 *
 * Blue component of the default color displayed in the sectors where no layer is active.
 */
#define LCDC_BGND_CL_B_MASK (0xFFU)
#define LCDC_BGND_CL_B_SHIFT (0U)
#define LCDC_BGND_CL_B_SET(x) (((uint32_t)(x) << LCDC_BGND_CL_B_SHIFT) & LCDC_BGND_CL_B_MASK)
#define LCDC_BGND_CL_B_GET(x) (((uint32_t)(x) & LCDC_BGND_CL_B_MASK) >> LCDC_BGND_CL_B_SHIFT)

/* Bitfield definition for register: DISP_WN_SIZE */
/*
 * Y (RW)
 *
 * Sets the display size vertical resolution in pixels.
 */
#define LCDC_DISP_WN_SIZE_Y_MASK (0xFFF0000UL)
#define LCDC_DISP_WN_SIZE_Y_SHIFT (16U)
#define LCDC_DISP_WN_SIZE_Y_SET(x) (((uint32_t)(x) << LCDC_DISP_WN_SIZE_Y_SHIFT) & LCDC_DISP_WN_SIZE_Y_MASK)
#define LCDC_DISP_WN_SIZE_Y_GET(x) (((uint32_t)(x) & LCDC_DISP_WN_SIZE_Y_MASK) >> LCDC_DISP_WN_SIZE_Y_SHIFT)

/*
 * X (RW)
 *
 * Sets the display size horizontal resolution in pixels.
 */
#define LCDC_DISP_WN_SIZE_X_MASK (0xFFFU)
#define LCDC_DISP_WN_SIZE_X_SHIFT (0U)
#define LCDC_DISP_WN_SIZE_X_SET(x) (((uint32_t)(x) << LCDC_DISP_WN_SIZE_X_SHIFT) & LCDC_DISP_WN_SIZE_X_MASK)
#define LCDC_DISP_WN_SIZE_X_GET(x) (((uint32_t)(x) & LCDC_DISP_WN_SIZE_X_MASK) >> LCDC_DISP_WN_SIZE_X_SHIFT)

/* Bitfield definition for register: HSYNC_PARA */
/*
 * FP (RW)
 *
 * HSYNC front-porch pulse width (in pixel clock cycles). If zero, indicates no front-porch for HSYNC
 */
#define LCDC_HSYNC_PARA_FP_MASK (0x7FC00000UL)
#define LCDC_HSYNC_PARA_FP_SHIFT (22U)
#define LCDC_HSYNC_PARA_FP_SET(x) (((uint32_t)(x) << LCDC_HSYNC_PARA_FP_SHIFT) & LCDC_HSYNC_PARA_FP_MASK)
#define LCDC_HSYNC_PARA_FP_GET(x) (((uint32_t)(x) & LCDC_HSYNC_PARA_FP_MASK) >> LCDC_HSYNC_PARA_FP_SHIFT)

/*
 * BP (RW)
 *
 * HSYNC back-porch pulse width (in pixel clock cycles). If zero, indicates no back-porch for HSYNC
 */
#define LCDC_HSYNC_PARA_BP_MASK (0xFF800UL)
#define LCDC_HSYNC_PARA_BP_SHIFT (11U)
#define LCDC_HSYNC_PARA_BP_SET(x) (((uint32_t)(x) << LCDC_HSYNC_PARA_BP_SHIFT) & LCDC_HSYNC_PARA_BP_MASK)
#define LCDC_HSYNC_PARA_BP_GET(x) (((uint32_t)(x) & LCDC_HSYNC_PARA_BP_MASK) >> LCDC_HSYNC_PARA_BP_SHIFT)

/*
 * PW (RW)
 *
 * HSYNC active pulse width (in pixel clock cycles). Pulse width has a minimum value of 1.
 */
#define LCDC_HSYNC_PARA_PW_MASK (0x1FFU)
#define LCDC_HSYNC_PARA_PW_SHIFT (0U)
#define LCDC_HSYNC_PARA_PW_SET(x) (((uint32_t)(x) << LCDC_HSYNC_PARA_PW_SHIFT) & LCDC_HSYNC_PARA_PW_MASK)
#define LCDC_HSYNC_PARA_PW_GET(x) (((uint32_t)(x) & LCDC_HSYNC_PARA_PW_MASK) >> LCDC_HSYNC_PARA_PW_SHIFT)

/* Bitfield definition for register: VSYNC_PARA */
/*
 * FP (RW)
 *
 * VSYNC front-porch pulse width (in horizontal line cycles). If zero, means no front-porch for VSYNC
 */
#define LCDC_VSYNC_PARA_FP_MASK (0x7FC00000UL)
#define LCDC_VSYNC_PARA_FP_SHIFT (22U)
#define LCDC_VSYNC_PARA_FP_SET(x) (((uint32_t)(x) << LCDC_VSYNC_PARA_FP_SHIFT) & LCDC_VSYNC_PARA_FP_MASK)
#define LCDC_VSYNC_PARA_FP_GET(x) (((uint32_t)(x) & LCDC_VSYNC_PARA_FP_MASK) >> LCDC_VSYNC_PARA_FP_SHIFT)

/*
 * BP (RW)
 *
 * VSYNC back-porch pulse width (in horizontal line cycles). If zero, means no back-porch for VSYNC
 */
#define LCDC_VSYNC_PARA_BP_MASK (0xFF800UL)
#define LCDC_VSYNC_PARA_BP_SHIFT (11U)
#define LCDC_VSYNC_PARA_BP_SET(x) (((uint32_t)(x) << LCDC_VSYNC_PARA_BP_SHIFT) & LCDC_VSYNC_PARA_BP_MASK)
#define LCDC_VSYNC_PARA_BP_GET(x) (((uint32_t)(x) & LCDC_VSYNC_PARA_BP_MASK) >> LCDC_VSYNC_PARA_BP_SHIFT)

/*
 * PW (RW)
 *
 * VSYNC active pulse width (in horizontal line cycles). Pulse width has a minimum value of 1.
 */
#define LCDC_VSYNC_PARA_PW_MASK (0x1FFU)
#define LCDC_VSYNC_PARA_PW_SHIFT (0U)
#define LCDC_VSYNC_PARA_PW_SET(x) (((uint32_t)(x) << LCDC_VSYNC_PARA_PW_SHIFT) & LCDC_VSYNC_PARA_PW_MASK)
#define LCDC_VSYNC_PARA_PW_GET(x) (((uint32_t)(x) & LCDC_VSYNC_PARA_PW_MASK) >> LCDC_VSYNC_PARA_PW_SHIFT)

/* Bitfield definition for register: DMA_ST */
/*
 * DMA_ERR (W1C)
 *
 * plane n axi error. W1C.
 */
#define LCDC_DMA_ST_DMA_ERR_MASK (0xFF000000UL)
#define LCDC_DMA_ST_DMA_ERR_SHIFT (24U)
#define LCDC_DMA_ST_DMA_ERR_SET(x) (((uint32_t)(x) << LCDC_DMA_ST_DMA_ERR_SHIFT) & LCDC_DMA_ST_DMA_ERR_MASK)
#define LCDC_DMA_ST_DMA_ERR_GET(x) (((uint32_t)(x) & LCDC_DMA_ST_DMA_ERR_MASK) >> LCDC_DMA_ST_DMA_ERR_SHIFT)

/*
 * DMA1_DONE (W1C)
 *
 * Plane n frame 1 dma done. W1C.
 */
#define LCDC_DMA_ST_DMA1_DONE_MASK (0xFF0000UL)
#define LCDC_DMA_ST_DMA1_DONE_SHIFT (16U)
#define LCDC_DMA_ST_DMA1_DONE_SET(x) (((uint32_t)(x) << LCDC_DMA_ST_DMA1_DONE_SHIFT) & LCDC_DMA_ST_DMA1_DONE_MASK)
#define LCDC_DMA_ST_DMA1_DONE_GET(x) (((uint32_t)(x) & LCDC_DMA_ST_DMA1_DONE_MASK) >> LCDC_DMA_ST_DMA1_DONE_SHIFT)

/*
 * DMA0_DONE (W1C)
 *
 * Plane n frame 0 dma done. W1C.
 */
#define LCDC_DMA_ST_DMA0_DONE_MASK (0xFF00U)
#define LCDC_DMA_ST_DMA0_DONE_SHIFT (8U)
#define LCDC_DMA_ST_DMA0_DONE_SET(x) (((uint32_t)(x) << LCDC_DMA_ST_DMA0_DONE_SHIFT) & LCDC_DMA_ST_DMA0_DONE_MASK)
#define LCDC_DMA_ST_DMA0_DONE_GET(x) (((uint32_t)(x) & LCDC_DMA_ST_DMA0_DONE_MASK) >> LCDC_DMA_ST_DMA0_DONE_SHIFT)

/* Bitfield definition for register: ST */
/*
 * URGENT_UNDERRUN (W1C)
 *
 * Asserted when the output buffer urgent underrun condition encountered
 */
#define LCDC_ST_URGENT_UNDERRUN_MASK (0x8U)
#define LCDC_ST_URGENT_UNDERRUN_SHIFT (3U)
#define LCDC_ST_URGENT_UNDERRUN_SET(x) (((uint32_t)(x) << LCDC_ST_URGENT_UNDERRUN_SHIFT) & LCDC_ST_URGENT_UNDERRUN_MASK)
#define LCDC_ST_URGENT_UNDERRUN_GET(x) (((uint32_t)(x) & LCDC_ST_URGENT_UNDERRUN_MASK) >> LCDC_ST_URGENT_UNDERRUN_SHIFT)

/*
 * VS_BLANK (W1C)
 *
 * Asserted when in vertical blanking period. At the start of VSYNC
 */
#define LCDC_ST_VS_BLANK_MASK (0x4U)
#define LCDC_ST_VS_BLANK_SHIFT (2U)
#define LCDC_ST_VS_BLANK_SET(x) (((uint32_t)(x) << LCDC_ST_VS_BLANK_SHIFT) & LCDC_ST_VS_BLANK_MASK)
#define LCDC_ST_VS_BLANK_GET(x) (((uint32_t)(x) & LCDC_ST_VS_BLANK_MASK) >> LCDC_ST_VS_BLANK_SHIFT)

/*
 * UNDERRUN (W1C)
 *
 * Asserted when the output buffer underrun condition encountered
 */
#define LCDC_ST_UNDERRUN_MASK (0x2U)
#define LCDC_ST_UNDERRUN_SHIFT (1U)
#define LCDC_ST_UNDERRUN_SET(x) (((uint32_t)(x) << LCDC_ST_UNDERRUN_SHIFT) & LCDC_ST_UNDERRUN_MASK)
#define LCDC_ST_UNDERRUN_GET(x) (((uint32_t)(x) & LCDC_ST_UNDERRUN_MASK) >> LCDC_ST_UNDERRUN_SHIFT)

/*
 * VSYNC (W1C)
 *
 * Asserted when in  vertical blanking period. At the end of VSYNC
 */
#define LCDC_ST_VSYNC_MASK (0x1U)
#define LCDC_ST_VSYNC_SHIFT (0U)
#define LCDC_ST_VSYNC_SET(x) (((uint32_t)(x) << LCDC_ST_VSYNC_SHIFT) & LCDC_ST_VSYNC_MASK)
#define LCDC_ST_VSYNC_GET(x) (((uint32_t)(x) & LCDC_ST_VSYNC_MASK) >> LCDC_ST_VSYNC_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * DMA_ERR (RW)
 *
 * Interrupt enable for DMA error
 */
#define LCDC_INT_EN_DMA_ERR_MASK (0xFF000000UL)
#define LCDC_INT_EN_DMA_ERR_SHIFT (24U)
#define LCDC_INT_EN_DMA_ERR_SET(x) (((uint32_t)(x) << LCDC_INT_EN_DMA_ERR_SHIFT) & LCDC_INT_EN_DMA_ERR_MASK)
#define LCDC_INT_EN_DMA_ERR_GET(x) (((uint32_t)(x) & LCDC_INT_EN_DMA_ERR_MASK) >> LCDC_INT_EN_DMA_ERR_SHIFT)

/*
 * DMA_DONE (RW)
 *
 * Interrupt enable for DMA done
 */
#define LCDC_INT_EN_DMA_DONE_MASK (0xFF0000UL)
#define LCDC_INT_EN_DMA_DONE_SHIFT (16U)
#define LCDC_INT_EN_DMA_DONE_SET(x) (((uint32_t)(x) << LCDC_INT_EN_DMA_DONE_SHIFT) & LCDC_INT_EN_DMA_DONE_MASK)
#define LCDC_INT_EN_DMA_DONE_GET(x) (((uint32_t)(x) & LCDC_INT_EN_DMA_DONE_MASK) >> LCDC_INT_EN_DMA_DONE_SHIFT)

/*
 * URGENT_UNDERRUN (RW)
 *
 * Asserted when the output buffer urgent underrun condition encountered
 */
#define LCDC_INT_EN_URGENT_UNDERRUN_MASK (0x8U)
#define LCDC_INT_EN_URGENT_UNDERRUN_SHIFT (3U)
#define LCDC_INT_EN_URGENT_UNDERRUN_SET(x) (((uint32_t)(x) << LCDC_INT_EN_URGENT_UNDERRUN_SHIFT) & LCDC_INT_EN_URGENT_UNDERRUN_MASK)
#define LCDC_INT_EN_URGENT_UNDERRUN_GET(x) (((uint32_t)(x) & LCDC_INT_EN_URGENT_UNDERRUN_MASK) >> LCDC_INT_EN_URGENT_UNDERRUN_SHIFT)

/*
 * VS_BLANK (RW)
 *
 * Interrupt enable for start of sof
 */
#define LCDC_INT_EN_VS_BLANK_MASK (0x4U)
#define LCDC_INT_EN_VS_BLANK_SHIFT (2U)
#define LCDC_INT_EN_VS_BLANK_SET(x) (((uint32_t)(x) << LCDC_INT_EN_VS_BLANK_SHIFT) & LCDC_INT_EN_VS_BLANK_MASK)
#define LCDC_INT_EN_VS_BLANK_GET(x) (((uint32_t)(x) & LCDC_INT_EN_VS_BLANK_MASK) >> LCDC_INT_EN_VS_BLANK_SHIFT)

/*
 * UNDERRUN (RW)
 *
 * Interrupt enable for underrun
 */
#define LCDC_INT_EN_UNDERRUN_MASK (0x2U)
#define LCDC_INT_EN_UNDERRUN_SHIFT (1U)
#define LCDC_INT_EN_UNDERRUN_SET(x) (((uint32_t)(x) << LCDC_INT_EN_UNDERRUN_SHIFT) & LCDC_INT_EN_UNDERRUN_MASK)
#define LCDC_INT_EN_UNDERRUN_GET(x) (((uint32_t)(x) & LCDC_INT_EN_UNDERRUN_MASK) >> LCDC_INT_EN_UNDERRUN_SHIFT)

/*
 * VSYNC (RW)
 *
 * Interrupt enable for end of sof
 */
#define LCDC_INT_EN_VSYNC_MASK (0x1U)
#define LCDC_INT_EN_VSYNC_SHIFT (0U)
#define LCDC_INT_EN_VSYNC_SET(x) (((uint32_t)(x) << LCDC_INT_EN_VSYNC_SHIFT) & LCDC_INT_EN_VSYNC_MASK)
#define LCDC_INT_EN_VSYNC_GET(x) (((uint32_t)(x) & LCDC_INT_EN_VSYNC_MASK) >> LCDC_INT_EN_VSYNC_SHIFT)

/* Bitfield definition for register: TXFIFO */
/*
 * THRSH (RW)
 *
 * Threshold to start the lcd raster (0--0x7F)
 */
#define LCDC_TXFIFO_THRSH_MASK (0xFFU)
#define LCDC_TXFIFO_THRSH_SHIFT (0U)
#define LCDC_TXFIFO_THRSH_SET(x) (((uint32_t)(x) << LCDC_TXFIFO_THRSH_SHIFT) & LCDC_TXFIFO_THRSH_MASK)
#define LCDC_TXFIFO_THRSH_GET(x) (((uint32_t)(x) & LCDC_TXFIFO_THRSH_MASK) >> LCDC_TXFIFO_THRSH_SHIFT)

/* Bitfield definition for register of struct array LAYER: LAYCTRL */
/*
 * PACK_DIR (RW)
 *
 * The byte sequence of the 4 bytes in a 32-bit word.
 * 1: {A0, A1, A2, A3} byte re-ordered.
 * 0: {A3, A2, A1, A0} the normal case with no byte re-order
 */
#define LCDC_LAYER_LAYCTRL_PACK_DIR_MASK (0x80000UL)
#define LCDC_LAYER_LAYCTRL_PACK_DIR_SHIFT (19U)
#define LCDC_LAYER_LAYCTRL_PACK_DIR_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_PACK_DIR_SHIFT) & LCDC_LAYER_LAYCTRL_PACK_DIR_MASK)
#define LCDC_LAYER_LAYCTRL_PACK_DIR_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_PACK_DIR_MASK) >> LCDC_LAYER_LAYCTRL_PACK_DIR_SHIFT)

/*
 * SHADOW_LOAD_EN (RW)
 *
 * Shadow Load Enable
 * The SHADOW_LOAD_EN bit is written to 1 by software after all DMA control registers are written. If set to 1, shadowed control registers are updated to the active control registers on internal logical VSYNC of next frame. If set to 0, shadowed control registers are not loaded into the active control registers. The previous active control register settings will be used to process the next frame. Hardware will automatically clear this bit, when the shadow registers are loaded to the active control regsisters.
 */
#define LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK (0x10000UL)
#define LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_SHIFT (16U)
#define LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_SHIFT) & LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK)
#define LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK) >> LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_SHIFT)

/*
 * YUV_FORMAT (RW)
 *
 * The YUV422 input format selection.
 * 00b - The YVYU422 8bit sequence is U1,Y1,V1,Y2
 * 01b - The YVYU422 8bit sequence is V1,Y1,U1,Y2
 * 10b - The YVYU422 8bit sequence is Y1,U1,Y2,V1
 * 11b - The YVYU422 8bit sequence is Y1,V1,Y2,U1
 * If not YUV422 mode,
 * FORMAT[0]: asserted to exchange sequence inside the bytes. Org [15:8]-->New[8:15], Org [7:0]-->New[0:7]. (First exchange)
 * FORMAT[1]: asserted to exchange the sequence of the odd and even 8 bits. Org Even [7:0]-->New[15:8], Org Odd [15:8]-->New[7:0]. (Second exchange)
 */
#define LCDC_LAYER_LAYCTRL_YUV_FORMAT_MASK (0xC000U)
#define LCDC_LAYER_LAYCTRL_YUV_FORMAT_SHIFT (14U)
#define LCDC_LAYER_LAYCTRL_YUV_FORMAT_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_YUV_FORMAT_SHIFT) & LCDC_LAYER_LAYCTRL_YUV_FORMAT_MASK)
#define LCDC_LAYER_LAYCTRL_YUV_FORMAT_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_YUV_FORMAT_MASK) >> LCDC_LAYER_LAYCTRL_YUV_FORMAT_SHIFT)

/*
 * PIXFORMAT (RW)
 *
 * Layer encoding format (bit per pixel)
 * 0000b - 1 bpp (pixel width must be multiples of 32), pixel sequence is from LSB to MSB in 32b word.
 * 0001b - 2 bpp (pixel width must be multiples of 16), pixel sequence is from LSB to MSB in 32b word.
 * 0010b - 4 bpp (pixel width must be multiples of 8), pixel sequence is from LSB to MSB in 32b word.
 * 0011b - 8 bpp  (pixel width must be multiples of 4), pixel sequence is from LSB to MSB in 32b word.
 * 0100b - 16 bpp (RGB565), the low byte contains the full R component.
 * 0111b - YCbCr422 (Only layer 0/1 can support this format), byte sequence determined by LAYCTRL[YUV_FORMAT]
 * 1001b - 32 bpp (ARGB8888), byte sequence as B,G,R,A
 * 1011b - Y8  (pixel width must be multiples of 4), byte sequence as Y1,Y2,Y3,Y4
 */
#define LCDC_LAYER_LAYCTRL_PIXFORMAT_MASK (0x3C00U)
#define LCDC_LAYER_LAYCTRL_PIXFORMAT_SHIFT (10U)
#define LCDC_LAYER_LAYCTRL_PIXFORMAT_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_PIXFORMAT_SHIFT) & LCDC_LAYER_LAYCTRL_PIXFORMAT_MASK)
#define LCDC_LAYER_LAYCTRL_PIXFORMAT_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_PIXFORMAT_MASK) >> LCDC_LAYER_LAYCTRL_PIXFORMAT_SHIFT)

/*
 * LOCALPHA_OP (RW)
 *
 * The usage of the LOCALPHA[7:0]: (The system alpha value is not the data valid mask, the non-zero alpha value per pixel indicates a valid pixel. If no such per pixel alpha value, it means all the pixels are valid)
 * 0: the LOCALPHA[7:0] is invalid, use the alpha value from the data stream
 * 1: the LOCALPHA[7:0] is used to override the alpha value in the data stream (useful when the data stream has no alpha info)
 * 2: the LOCALPHA[7:0] is used to scale the alpha value from the data stream
 * Others: Reserved
 */
#define LCDC_LAYER_LAYCTRL_LOCALPHA_OP_MASK (0x300U)
#define LCDC_LAYER_LAYCTRL_LOCALPHA_OP_SHIFT (8U)
#define LCDC_LAYER_LAYCTRL_LOCALPHA_OP_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_LOCALPHA_OP_SHIFT) & LCDC_LAYER_LAYCTRL_LOCALPHA_OP_MASK)
#define LCDC_LAYER_LAYCTRL_LOCALPHA_OP_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_LOCALPHA_OP_MASK) >> LCDC_LAYER_LAYCTRL_LOCALPHA_OP_SHIFT)

/*
 * INALPHA_OP (RW)
 *
 * The usage of the INALPHA[7:0]: (The system alpha value is not the data valid mask, the non-zero alpha value per pixel indicates a valid pixel. If no such per pixel alpha value, it means all the pixels are valid)
 * 0: the INALPHA[7:0] is invalid, use the alpha value from previous pipeline
 * 1: the INALPHA[7:0] is used to override the alpha value from previous pipeline.  (useful when the corresponding data stream has no alpha info)
 * 2: the INALPHA[7:0] is used to scale the alpha value from previous pipeline
 * Others: Reserved
 */
#define LCDC_LAYER_LAYCTRL_INALPHA_OP_MASK (0xC0U)
#define LCDC_LAYER_LAYCTRL_INALPHA_OP_SHIFT (6U)
#define LCDC_LAYER_LAYCTRL_INALPHA_OP_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_INALPHA_OP_SHIFT) & LCDC_LAYER_LAYCTRL_INALPHA_OP_MASK)
#define LCDC_LAYER_LAYCTRL_INALPHA_OP_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_INALPHA_OP_MASK) >> LCDC_LAYER_LAYCTRL_INALPHA_OP_SHIFT)

/*
 * AB_MODE (RW)
 *
 * Alpha Blending Mode
 * 0: SKBlendMode_Clear;
 * 1: SKBlendMode_Src ;
 * 2: SKBlendMode_Dst
 * 3: SKBlendMode_SrcOver
 * 4: SKBlendMode_DstOver
 * 5: SKBlendMode_SrcIn
 * 6: SKBlendMode_DstIn
 * 7: SKBlendMode_SrcOut
 * 8: SKBlendMode_DstOut
 * 9: SKBlendMode_SrcATop
 * 10: SKBlendMode_DstATop
 * 11: SKBlendMode_Xor
 * 12: SKBlendMode_Plus    (The conventional blending mode)
 * 13: SKBlendMode_Modulate
 * 14: SRC org
 * 15: DST org
 * Others: Reserved.
 */
#define LCDC_LAYER_LAYCTRL_AB_MODE_MASK (0x3CU)
#define LCDC_LAYER_LAYCTRL_AB_MODE_SHIFT (2U)
#define LCDC_LAYER_LAYCTRL_AB_MODE_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_AB_MODE_SHIFT) & LCDC_LAYER_LAYCTRL_AB_MODE_MASK)
#define LCDC_LAYER_LAYCTRL_AB_MODE_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_AB_MODE_MASK) >> LCDC_LAYER_LAYCTRL_AB_MODE_SHIFT)

/*
 * EN (RW)
 *
 * Asserted when the layer is enabled. If this layer is not enabled, it means a bypassing plane.
 */
#define LCDC_LAYER_LAYCTRL_EN_MASK (0x1U)
#define LCDC_LAYER_LAYCTRL_EN_SHIFT (0U)
#define LCDC_LAYER_LAYCTRL_EN_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYCTRL_EN_SHIFT) & LCDC_LAYER_LAYCTRL_EN_MASK)
#define LCDC_LAYER_LAYCTRL_EN_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYCTRL_EN_MASK) >> LCDC_LAYER_LAYCTRL_EN_SHIFT)

/* Bitfield definition for register of struct array LAYER: ALPHAS */
/*
 * LOCD (RW)
 *
 * The system alpha value for the data stream of current layer stream (SRC)
 */
#define LCDC_LAYER_ALPHAS_LOCD_MASK (0xFF00U)
#define LCDC_LAYER_ALPHAS_LOCD_SHIFT (8U)
#define LCDC_LAYER_ALPHAS_LOCD_SET(x) (((uint32_t)(x) << LCDC_LAYER_ALPHAS_LOCD_SHIFT) & LCDC_LAYER_ALPHAS_LOCD_MASK)
#define LCDC_LAYER_ALPHAS_LOCD_GET(x) (((uint32_t)(x) & LCDC_LAYER_ALPHAS_LOCD_MASK) >> LCDC_LAYER_ALPHAS_LOCD_SHIFT)

/*
 * IND (RW)
 *
 * The system alpha value for the input stream from previous stage (DST)
 */
#define LCDC_LAYER_ALPHAS_IND_MASK (0xFFU)
#define LCDC_LAYER_ALPHAS_IND_SHIFT (0U)
#define LCDC_LAYER_ALPHAS_IND_SET(x) (((uint32_t)(x) << LCDC_LAYER_ALPHAS_IND_SHIFT) & LCDC_LAYER_ALPHAS_IND_MASK)
#define LCDC_LAYER_ALPHAS_IND_GET(x) (((uint32_t)(x) & LCDC_LAYER_ALPHAS_IND_MASK) >> LCDC_LAYER_ALPHAS_IND_SHIFT)

/* Bitfield definition for register of struct array LAYER: LAYSIZE */
/*
 * HEIGHT (RW)
 *
 * Height of the layer in pixels
 */
#define LCDC_LAYER_LAYSIZE_HEIGHT_MASK (0xFFF0000UL)
#define LCDC_LAYER_LAYSIZE_HEIGHT_SHIFT (16U)
#define LCDC_LAYER_LAYSIZE_HEIGHT_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYSIZE_HEIGHT_SHIFT) & LCDC_LAYER_LAYSIZE_HEIGHT_MASK)
#define LCDC_LAYER_LAYSIZE_HEIGHT_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYSIZE_HEIGHT_MASK) >> LCDC_LAYER_LAYSIZE_HEIGHT_SHIFT)

/*
 * WIDTH (RW)
 *
 * Width of the layer in pixels (Note: not actual width-1)
 * The layer width must be in multiples of the number of pixels that can be stored in 32 bits, and therefore differs depending on color encoding. For example, if 2 bits per pixel format is used, then the layer width must be configured in multiples of 16.
 */
#define LCDC_LAYER_LAYSIZE_WIDTH_MASK (0xFFFU)
#define LCDC_LAYER_LAYSIZE_WIDTH_SHIFT (0U)
#define LCDC_LAYER_LAYSIZE_WIDTH_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYSIZE_WIDTH_SHIFT) & LCDC_LAYER_LAYSIZE_WIDTH_MASK)
#define LCDC_LAYER_LAYSIZE_WIDTH_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYSIZE_WIDTH_MASK) >> LCDC_LAYER_LAYSIZE_WIDTH_SHIFT)

/* Bitfield definition for register of struct array LAYER: LAYPOS */
/*
 * Y (RW)
 *
 * The vertical position of top row of the layer, where 0 is the top row of the panel, positive values are below the top row of the panel.
 */
#define LCDC_LAYER_LAYPOS_Y_MASK (0xFFFF0000UL)
#define LCDC_LAYER_LAYPOS_Y_SHIFT (16U)
#define LCDC_LAYER_LAYPOS_Y_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYPOS_Y_SHIFT) & LCDC_LAYER_LAYPOS_Y_MASK)
#define LCDC_LAYER_LAYPOS_Y_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYPOS_Y_MASK) >> LCDC_LAYER_LAYPOS_Y_SHIFT)

/*
 * X (RW)
 *
 * The horizontal position of left-hand column of the layer, where 0 is the left-hand column of the panel, positive values are to the right the left-hand column of the panel.
 */
#define LCDC_LAYER_LAYPOS_X_MASK (0xFFFFU)
#define LCDC_LAYER_LAYPOS_X_SHIFT (0U)
#define LCDC_LAYER_LAYPOS_X_SET(x) (((uint32_t)(x) << LCDC_LAYER_LAYPOS_X_SHIFT) & LCDC_LAYER_LAYPOS_X_MASK)
#define LCDC_LAYER_LAYPOS_X_GET(x) (((uint32_t)(x) & LCDC_LAYER_LAYPOS_X_MASK) >> LCDC_LAYER_LAYPOS_X_SHIFT)

/* Bitfield definition for register of struct array LAYER: START0 */
/*
 * ADDR0 (RW)
 *
 * Input buffer Start address 0
 */
#define LCDC_LAYER_START0_ADDR0_MASK (0xFFFFFFFFUL)
#define LCDC_LAYER_START0_ADDR0_SHIFT (0U)
#define LCDC_LAYER_START0_ADDR0_SET(x) (((uint32_t)(x) << LCDC_LAYER_START0_ADDR0_SHIFT) & LCDC_LAYER_START0_ADDR0_MASK)
#define LCDC_LAYER_START0_ADDR0_GET(x) (((uint32_t)(x) & LCDC_LAYER_START0_ADDR0_MASK) >> LCDC_LAYER_START0_ADDR0_SHIFT)

/* Bitfield definition for register of struct array LAYER: LINECFG */
/*
 * MPT_SIZE (RW)
 *
 * Maximal Per Transfer Data Size:
 * 0: 64 bytes
 * 1: 128 bytes
 * 2: 256 bytes
 * 3: 512 bytes
 * 4: 1024 bytes
 */
#define LCDC_LAYER_LINECFG_MPT_SIZE_MASK (0xE0000000UL)
#define LCDC_LAYER_LINECFG_MPT_SIZE_SHIFT (29U)
#define LCDC_LAYER_LINECFG_MPT_SIZE_SET(x) (((uint32_t)(x) << LCDC_LAYER_LINECFG_MPT_SIZE_SHIFT) & LCDC_LAYER_LINECFG_MPT_SIZE_MASK)
#define LCDC_LAYER_LINECFG_MPT_SIZE_GET(x) (((uint32_t)(x) & LCDC_LAYER_LINECFG_MPT_SIZE_MASK) >> LCDC_LAYER_LINECFG_MPT_SIZE_SHIFT)

/*
 * MAX_OT (RW)
 *
 * the number of outstanding axi read transactions.
 * If zero, it means max 8.
 */
#define LCDC_LAYER_LINECFG_MAX_OT_MASK (0xE00000UL)
#define LCDC_LAYER_LINECFG_MAX_OT_SHIFT (21U)
#define LCDC_LAYER_LINECFG_MAX_OT_SET(x) (((uint32_t)(x) << LCDC_LAYER_LINECFG_MAX_OT_SHIFT) & LCDC_LAYER_LINECFG_MAX_OT_MASK)
#define LCDC_LAYER_LINECFG_MAX_OT_GET(x) (((uint32_t)(x) & LCDC_LAYER_LINECFG_MAX_OT_MASK) >> LCDC_LAYER_LINECFG_MAX_OT_SHIFT)

/*
 * PITCH (RW)
 *
 * Number of bytes between 2 vertically adjacent pixels in system memory. Byte granularity is supported, but SW should align to 64B boundary.
 */
#define LCDC_LAYER_LINECFG_PITCH_MASK (0xFFFFU)
#define LCDC_LAYER_LINECFG_PITCH_SHIFT (0U)
#define LCDC_LAYER_LINECFG_PITCH_SET(x) (((uint32_t)(x) << LCDC_LAYER_LINECFG_PITCH_SHIFT) & LCDC_LAYER_LINECFG_PITCH_MASK)
#define LCDC_LAYER_LINECFG_PITCH_GET(x) (((uint32_t)(x) & LCDC_LAYER_LINECFG_PITCH_MASK) >> LCDC_LAYER_LINECFG_PITCH_SHIFT)

/* Bitfield definition for register of struct array LAYER: BG_CL */
/*
 * ARGB (RW)
 *
 * ARGB8888. It is only useful in the last active stage in the pipeline.
 */
#define LCDC_LAYER_BG_CL_ARGB_MASK (0xFFFFFFFFUL)
#define LCDC_LAYER_BG_CL_ARGB_SHIFT (0U)
#define LCDC_LAYER_BG_CL_ARGB_SET(x) (((uint32_t)(x) << LCDC_LAYER_BG_CL_ARGB_SHIFT) & LCDC_LAYER_BG_CL_ARGB_MASK)
#define LCDC_LAYER_BG_CL_ARGB_GET(x) (((uint32_t)(x) & LCDC_LAYER_BG_CL_ARGB_MASK) >> LCDC_LAYER_BG_CL_ARGB_SHIFT)

/* Bitfield definition for register of struct array LAYER: CSC_COEF0 */
/*
 * YCBCR_MODE (RW)
 *
 * This bit changes the behavior when performing U/V converting.
 * 0b - Converting YUV to RGB data
 * 1b - Converting YCbCr to RGB data
 */
#define LCDC_LAYER_CSC_COEF0_YCBCR_MODE_MASK (0x80000000UL)
#define LCDC_LAYER_CSC_COEF0_YCBCR_MODE_SHIFT (31U)
#define LCDC_LAYER_CSC_COEF0_YCBCR_MODE_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF0_YCBCR_MODE_SHIFT) & LCDC_LAYER_CSC_COEF0_YCBCR_MODE_MASK)
#define LCDC_LAYER_CSC_COEF0_YCBCR_MODE_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF0_YCBCR_MODE_MASK) >> LCDC_LAYER_CSC_COEF0_YCBCR_MODE_SHIFT)

/*
 * ENABLE (RW)
 *
 * Enable the CSC unit in the LCDC plane data path.
 * 0b - The CSC is bypassed and the input pixels are RGB data already
 * 1b - The CSC is enabled and the pixels will be converted to RGB data
 * This bit will be shadowed.
 */
#define LCDC_LAYER_CSC_COEF0_ENABLE_MASK (0x40000000UL)
#define LCDC_LAYER_CSC_COEF0_ENABLE_SHIFT (30U)
#define LCDC_LAYER_CSC_COEF0_ENABLE_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF0_ENABLE_SHIFT) & LCDC_LAYER_CSC_COEF0_ENABLE_MASK)
#define LCDC_LAYER_CSC_COEF0_ENABLE_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF0_ENABLE_MASK) >> LCDC_LAYER_CSC_COEF0_ENABLE_SHIFT)

/*
 * C0 (RW)
 *
 * Two's compliment Y multiplier coefficient C0. YUV=0x100 (1.000) YCbCr=0x12A (1.164)
 */
#define LCDC_LAYER_CSC_COEF0_C0_MASK (0x1FFC0000UL)
#define LCDC_LAYER_CSC_COEF0_C0_SHIFT (18U)
#define LCDC_LAYER_CSC_COEF0_C0_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF0_C0_SHIFT) & LCDC_LAYER_CSC_COEF0_C0_MASK)
#define LCDC_LAYER_CSC_COEF0_C0_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF0_C0_MASK) >> LCDC_LAYER_CSC_COEF0_C0_SHIFT)

/*
 * UV_OFFSET (RW)
 *
 * Two's compliment phase offset implicit for CbCr data UV_OFFSET. Generally used for YCbCr to RGB conversion.
 * YCbCr=0x180, YUV=0x000 (typically -128 or 0x180 to indicate normalized -0.5 to 0.5 range).
 */
#define LCDC_LAYER_CSC_COEF0_UV_OFFSET_MASK (0x3FE00UL)
#define LCDC_LAYER_CSC_COEF0_UV_OFFSET_SHIFT (9U)
#define LCDC_LAYER_CSC_COEF0_UV_OFFSET_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF0_UV_OFFSET_SHIFT) & LCDC_LAYER_CSC_COEF0_UV_OFFSET_MASK)
#define LCDC_LAYER_CSC_COEF0_UV_OFFSET_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF0_UV_OFFSET_MASK) >> LCDC_LAYER_CSC_COEF0_UV_OFFSET_SHIFT)

/*
 * Y_OFFSET (RW)
 *
 * Two's compliment amplitude offset implicit in the Y data Y_OFFSET. For YUV, this is typically 0 and for YCbCr, this is
 * typically -16 (0x1F0).
 */
#define LCDC_LAYER_CSC_COEF0_Y_OFFSET_MASK (0x1FFU)
#define LCDC_LAYER_CSC_COEF0_Y_OFFSET_SHIFT (0U)
#define LCDC_LAYER_CSC_COEF0_Y_OFFSET_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF0_Y_OFFSET_SHIFT) & LCDC_LAYER_CSC_COEF0_Y_OFFSET_MASK)
#define LCDC_LAYER_CSC_COEF0_Y_OFFSET_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF0_Y_OFFSET_MASK) >> LCDC_LAYER_CSC_COEF0_Y_OFFSET_SHIFT)

/* Bitfield definition for register of struct array LAYER: CSC_COEF1 */
/*
 * C1 (RW)
 *
 * Two's compliment Red V/Cr multiplier coefficient C1. YUV=0x123 (1.140) YCbCr=0x198 (1.596).
 */
#define LCDC_LAYER_CSC_COEF1_C1_MASK (0x7FF0000UL)
#define LCDC_LAYER_CSC_COEF1_C1_SHIFT (16U)
#define LCDC_LAYER_CSC_COEF1_C1_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF1_C1_SHIFT) & LCDC_LAYER_CSC_COEF1_C1_MASK)
#define LCDC_LAYER_CSC_COEF1_C1_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF1_C1_MASK) >> LCDC_LAYER_CSC_COEF1_C1_SHIFT)

/*
 * C4 (RW)
 *
 * Two's compliment Blue U/Cb multiplier coefficient C4. YUV=0x208 (2.032) YCbCr=0x204 (2.017).
 */
#define LCDC_LAYER_CSC_COEF1_C4_MASK (0x7FFU)
#define LCDC_LAYER_CSC_COEF1_C4_SHIFT (0U)
#define LCDC_LAYER_CSC_COEF1_C4_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF1_C4_SHIFT) & LCDC_LAYER_CSC_COEF1_C4_MASK)
#define LCDC_LAYER_CSC_COEF1_C4_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF1_C4_MASK) >> LCDC_LAYER_CSC_COEF1_C4_SHIFT)

/* Bitfield definition for register of struct array LAYER: CSC_COEF2 */
/*
 * C2 (RW)
 *
 * Two's compliment Green V/Cr multiplier coefficient C2. YUV=0x76B (-0.581) YCbCr=0x730 (-0.813).
 */
#define LCDC_LAYER_CSC_COEF2_C2_MASK (0x7FF0000UL)
#define LCDC_LAYER_CSC_COEF2_C2_SHIFT (16U)
#define LCDC_LAYER_CSC_COEF2_C2_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF2_C2_SHIFT) & LCDC_LAYER_CSC_COEF2_C2_MASK)
#define LCDC_LAYER_CSC_COEF2_C2_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF2_C2_MASK) >> LCDC_LAYER_CSC_COEF2_C2_SHIFT)

/*
 * C3 (RW)
 *
 * Two's compliment Green U/Cb multiplier coefficient C3. YUV=0x79C (-0.394) YCbCr=0x79C (-0.392).
 */
#define LCDC_LAYER_CSC_COEF2_C3_MASK (0x7FFU)
#define LCDC_LAYER_CSC_COEF2_C3_SHIFT (0U)
#define LCDC_LAYER_CSC_COEF2_C3_SET(x) (((uint32_t)(x) << LCDC_LAYER_CSC_COEF2_C3_SHIFT) & LCDC_LAYER_CSC_COEF2_C3_MASK)
#define LCDC_LAYER_CSC_COEF2_C3_GET(x) (((uint32_t)(x) & LCDC_LAYER_CSC_COEF2_C3_MASK) >> LCDC_LAYER_CSC_COEF2_C3_SHIFT)

/* Bitfield definition for register: CLUT_LOAD */
/*
 * SEL_NUM (RW)
 *
 * Selected CLUT Number
 * The SEL_CLUT_NUM is used to select which plane's CLUT need to be updated. The hardware can only backup one CLUT setting and load, so the SEL_CLUT_NUM can't be changed when CLUT_LOAD[UPDATE_EN] is 1.
 * . 3'h0 - PLANE 0
 * . 3'h1 - PLANE 1
 * . ------
 * . 3'h7 - PLANE 7
 * CLUT 8 can be modified via APB even when display is on.
 * Currently CLUT for plane 0..7 cannot be modified via APB when display is on.  Can only be updated via CLUT_LOAD[UPDATE_EN] bit.
 */
#define LCDC_CLUT_LOAD_SEL_NUM_MASK (0x70U)
#define LCDC_CLUT_LOAD_SEL_NUM_SHIFT (4U)
#define LCDC_CLUT_LOAD_SEL_NUM_SET(x) (((uint32_t)(x) << LCDC_CLUT_LOAD_SEL_NUM_SHIFT) & LCDC_CLUT_LOAD_SEL_NUM_MASK)
#define LCDC_CLUT_LOAD_SEL_NUM_GET(x) (((uint32_t)(x) & LCDC_CLUT_LOAD_SEL_NUM_MASK) >> LCDC_CLUT_LOAD_SEL_NUM_SHIFT)

/*
 * UPDATE_EN (RW)
 *
 * CLUT Update Enable
 * The bit is written to 1 when software want to update the Color Look Up Tables during display.
 * If set to 1, software update selected CLUT due to SEL_CLUT_NUM setting, the table will be copied from CLUT8 during vertical blanking period after SHADOW_LOAD_EN is set to 1.
 * If set to 0, software can update CLUT8 directly according to the CLUT memory map.
 * Hardware will automatically clear this bit when selected CLUT is updated according to SEL_CLUT_NUM.
 */
#define LCDC_CLUT_LOAD_UPDATE_EN_MASK (0x1U)
#define LCDC_CLUT_LOAD_UPDATE_EN_SHIFT (0U)
#define LCDC_CLUT_LOAD_UPDATE_EN_SET(x) (((uint32_t)(x) << LCDC_CLUT_LOAD_UPDATE_EN_SHIFT) & LCDC_CLUT_LOAD_UPDATE_EN_MASK)
#define LCDC_CLUT_LOAD_UPDATE_EN_GET(x) (((uint32_t)(x) & LCDC_CLUT_LOAD_UPDATE_EN_MASK) >> LCDC_CLUT_LOAD_UPDATE_EN_SHIFT)



/* LAYER register group index macro definition */
#define LCDC_LAYER_0 (0UL)
#define LCDC_LAYER_1 (1UL)
#define LCDC_LAYER_2 (2UL)
#define LCDC_LAYER_3 (3UL)
#define LCDC_LAYER_4 (4UL)
#define LCDC_LAYER_5 (5UL)
#define LCDC_LAYER_6 (6UL)
#define LCDC_LAYER_7 (7UL)


#endif /* HPM_LCDC_H */
