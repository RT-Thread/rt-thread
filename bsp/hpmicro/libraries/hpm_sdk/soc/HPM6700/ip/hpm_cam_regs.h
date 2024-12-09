/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_CAM_H
#define HPM_CAM_H

typedef struct {
    __RW uint32_t CR1;                         /* 0x0: Control Register */
    __RW uint32_t INT_EN;                      /* 0x4: Interrupt Enable Register */
    __R  uint8_t  RESERVED0[8];                /* 0x8 - 0xF: Reserved */
    __RW uint32_t CR2;                         /* 0x10: Control 2 Register */
    __R  uint8_t  RESERVED1[16];               /* 0x14 - 0x23: Reserved */
    __RW uint32_t STA;                         /* 0x24: Status Register */
    __R  uint8_t  RESERVED2[8];                /* 0x28 - 0x2F: Reserved */
    __RW uint32_t DMASA_FB1;                   /* 0x30: Pixel DMA Frame Buffer 1 Address */
    __RW uint32_t DMASA_FB2;                   /* 0x34: Pixel DMA Frame Buffer 2 Address */
    __RW uint32_t BUF_PARA;                    /* 0x38: Buffer Parameters Register */
    __RW uint32_t IDEAL_WN_SIZE;               /* 0x3C: Ideal Image Size Register */
    __R  uint8_t  RESERVED3[12];               /* 0x40 - 0x4B: Reserved */
    __RW uint32_t CR18;                        /* 0x4C: Control CR18 Register */
    __RW uint32_t DMASA_UV1;                   /* 0x50: Pixel UV DMA Frame Buffer 1 Address */
    __RW uint32_t DMASA_UV2;                   /* 0x54: Pixel UV DMA Frame Buffer 2 Address */
    __RW uint32_t CR20;                        /* 0x58: Control CR20 Register */
    __R  uint8_t  RESERVED4[20];               /* 0x5C - 0x6F: Reserved */
    __RW uint32_t CSC_COEF0;                   /* 0x70: Color Space Conversion Config Register 0 */
    __RW uint32_t CSC_COEF1;                   /* 0x74: Color Space Conversion Config Register 1 */
    __RW uint32_t CSC_COEF2;                   /* 0x78: Color Space Conversion Config Register 2 */
    __RW uint32_t CLRKEY_LOW;                  /* 0x7C: Low Color Key Register */
    __RW uint32_t CLRKEY_HIGH;                 /* 0x80: High Color Key Register */
    __R  uint8_t  RESERVED5[12];               /* 0x84 - 0x8F: Reserved */
    __R  uint32_t HISTOGRAM_FIFO[256];         /* 0x90 - 0x48C: Histogram Registers */
} CAM_Type;


/* Bitfield definition for register: CR1 */
/*
 * COLOR_EXT (RW)
 *
 * If asserted, will change the output color to ARGB8888 mode. Used by input color as RGB565, RGB888, YUV888, etc.
 * The byte sequence is B,G,R,A. Depends on correct CR2[ClrBitFormat] configuration.
 */
#define CAM_CR1_COLOR_EXT_MASK (0x20000000UL)
#define CAM_CR1_COLOR_EXT_SHIFT (29U)
#define CAM_CR1_COLOR_EXT_SET(x) (((uint32_t)(x) << CAM_CR1_COLOR_EXT_SHIFT) & CAM_CR1_COLOR_EXT_MASK)
#define CAM_CR1_COLOR_EXT_GET(x) (((uint32_t)(x) & CAM_CR1_COLOR_EXT_MASK) >> CAM_CR1_COLOR_EXT_SHIFT)

/*
 * INV_PIXCLK (RW)
 *
 * invert pixclk pad input before it is used
 */
#define CAM_CR1_INV_PIXCLK_MASK (0x10000000UL)
#define CAM_CR1_INV_PIXCLK_SHIFT (28U)
#define CAM_CR1_INV_PIXCLK_SET(x) (((uint32_t)(x) << CAM_CR1_INV_PIXCLK_SHIFT) & CAM_CR1_INV_PIXCLK_MASK)
#define CAM_CR1_INV_PIXCLK_GET(x) (((uint32_t)(x) & CAM_CR1_INV_PIXCLK_MASK) >> CAM_CR1_INV_PIXCLK_SHIFT)

/*
 * INV_HSYNC (RW)
 *
 * invert hsync pad input before it is used
 */
#define CAM_CR1_INV_HSYNC_MASK (0x8000000UL)
#define CAM_CR1_INV_HSYNC_SHIFT (27U)
#define CAM_CR1_INV_HSYNC_SET(x) (((uint32_t)(x) << CAM_CR1_INV_HSYNC_SHIFT) & CAM_CR1_INV_HSYNC_MASK)
#define CAM_CR1_INV_HSYNC_GET(x) (((uint32_t)(x) & CAM_CR1_INV_HSYNC_MASK) >> CAM_CR1_INV_HSYNC_SHIFT)

/*
 * INV_VSYNC (RW)
 *
 * invert vsync pad input before it is used
 */
#define CAM_CR1_INV_VSYNC_MASK (0x4000000UL)
#define CAM_CR1_INV_VSYNC_SHIFT (26U)
#define CAM_CR1_INV_VSYNC_SET(x) (((uint32_t)(x) << CAM_CR1_INV_VSYNC_SHIFT) & CAM_CR1_INV_VSYNC_MASK)
#define CAM_CR1_INV_VSYNC_GET(x) (((uint32_t)(x) & CAM_CR1_INV_VSYNC_MASK) >> CAM_CR1_INV_VSYNC_SHIFT)

/*
 * SWAP16_EN (RW)
 *
 * SWAP 16-Bit Enable. This bit enables the swapping of 16-bit data. Data is packed from 8-bit or 10-bit to 32-bit first (according to the setting of PACK_DIR) and then swapped as 16-bit words before being put into the RX FIFO. The action of the bit only affects the RX FIFO.
 * NOTE: Example of swapping enabled:
 * Data input to FIFO = 0x11223344
 * Data in RX FIFO = 0x 33441122
 * NOTE: Example of swapping disabled:
 * Data input to FIFO = 0x11223344
 * Data in RX FIFO = 0x11223344
 * 0 Disable swapping
 * 1 Enable swapping
 */
#define CAM_CR1_SWAP16_EN_MASK (0x2000000UL)
#define CAM_CR1_SWAP16_EN_SHIFT (25U)
#define CAM_CR1_SWAP16_EN_SET(x) (((uint32_t)(x) << CAM_CR1_SWAP16_EN_SHIFT) & CAM_CR1_SWAP16_EN_MASK)
#define CAM_CR1_SWAP16_EN_GET(x) (((uint32_t)(x) & CAM_CR1_SWAP16_EN_MASK) >> CAM_CR1_SWAP16_EN_SHIFT)

/*
 * PACK_DIR (RW)
 *
 * Data Packing Direction. This bit Controls how 8-bit/10-bit image data is packed into 32-bit RX FIFO.
 * 0 Pack from LSB first. For image data, 0x11, 0x22, 0x33, 0x44, it will appear as 0x44332211 in RX FIFO.
 * 1 Pack from MSB first. For image data, 0x11, 0x22, 0x33, 0x44, it will appear as 0x11223344 in RX FIFO.
 */
#define CAM_CR1_PACK_DIR_MASK (0x1000000UL)
#define CAM_CR1_PACK_DIR_SHIFT (24U)
#define CAM_CR1_PACK_DIR_SET(x) (((uint32_t)(x) << CAM_CR1_PACK_DIR_SHIFT) & CAM_CR1_PACK_DIR_MASK)
#define CAM_CR1_PACK_DIR_GET(x) (((uint32_t)(x) & CAM_CR1_PACK_DIR_MASK) >> CAM_CR1_PACK_DIR_SHIFT)

/*
 * RESTART_BUSPTR (RW)
 *
 * force to restart the bus pointer at the every end of the sof period, and at the same time, clr the fifo pointer
 */
#define CAM_CR1_RESTART_BUSPTR_MASK (0x800000UL)
#define CAM_CR1_RESTART_BUSPTR_SHIFT (23U)
#define CAM_CR1_RESTART_BUSPTR_SET(x) (((uint32_t)(x) << CAM_CR1_RESTART_BUSPTR_SHIFT) & CAM_CR1_RESTART_BUSPTR_MASK)
#define CAM_CR1_RESTART_BUSPTR_GET(x) (((uint32_t)(x) & CAM_CR1_RESTART_BUSPTR_MASK) >> CAM_CR1_RESTART_BUSPTR_SHIFT)

/*
 * ASYNC_RXFIFO_CLR (RW)
 *
 * ASynchronous Rx FIFO Clear.
 * When asserted, this bit clears RXFIFO immediately.
 * It will be auto-cleared.
 */
#define CAM_CR1_ASYNC_RXFIFO_CLR_MASK (0x100000UL)
#define CAM_CR1_ASYNC_RXFIFO_CLR_SHIFT (20U)
#define CAM_CR1_ASYNC_RXFIFO_CLR_SET(x) (((uint32_t)(x) << CAM_CR1_ASYNC_RXFIFO_CLR_SHIFT) & CAM_CR1_ASYNC_RXFIFO_CLR_MASK)
#define CAM_CR1_ASYNC_RXFIFO_CLR_GET(x) (((uint32_t)(x) & CAM_CR1_ASYNC_RXFIFO_CLR_MASK) >> CAM_CR1_ASYNC_RXFIFO_CLR_SHIFT)

/*
 * SYNC_RXFIFO_CLR (RW)
 *
 * Synchronous Rx FIFO Clear.
 * When asserted, this bit clears RXFIFO on every SOF.
 */
#define CAM_CR1_SYNC_RXFIFO_CLR_MASK (0x80000UL)
#define CAM_CR1_SYNC_RXFIFO_CLR_SHIFT (19U)
#define CAM_CR1_SYNC_RXFIFO_CLR_SET(x) (((uint32_t)(x) << CAM_CR1_SYNC_RXFIFO_CLR_SHIFT) & CAM_CR1_SYNC_RXFIFO_CLR_MASK)
#define CAM_CR1_SYNC_RXFIFO_CLR_GET(x) (((uint32_t)(x) & CAM_CR1_SYNC_RXFIFO_CLR_MASK) >> CAM_CR1_SYNC_RXFIFO_CLR_SHIFT)

/*
 * SOF_INT_POL (RW)
 *
 * SOF Interrupt Polarity. This bit controls the condition that generates an SOF interrupt.
 * 0 SOF interrupt is generated on SOF falling edge
 * 1 SOF interrupt is generated on SOF rising edge
 */
#define CAM_CR1_SOF_INT_POL_MASK (0x20000UL)
#define CAM_CR1_SOF_INT_POL_SHIFT (17U)
#define CAM_CR1_SOF_INT_POL_SET(x) (((uint32_t)(x) << CAM_CR1_SOF_INT_POL_SHIFT) & CAM_CR1_SOF_INT_POL_MASK)
#define CAM_CR1_SOF_INT_POL_GET(x) (((uint32_t)(x) & CAM_CR1_SOF_INT_POL_MASK) >> CAM_CR1_SOF_INT_POL_SHIFT)

/*
 * INV_DATA (RW)
 *
 * Invert Data Input. This bit enables or disables internal inverters on the data lines.
 * 0 CAM_D data lines are directly applied to internal circuitry
 * 1 CAM_D data lines are inverted before applied to internal circuitry
 */
#define CAM_CR1_INV_DATA_MASK (0x8000U)
#define CAM_CR1_INV_DATA_SHIFT (15U)
#define CAM_CR1_INV_DATA_SET(x) (((uint32_t)(x) << CAM_CR1_INV_DATA_SHIFT) & CAM_CR1_INV_DATA_MASK)
#define CAM_CR1_INV_DATA_GET(x) (((uint32_t)(x) & CAM_CR1_INV_DATA_MASK) >> CAM_CR1_INV_DATA_SHIFT)

/*
 * STORAGE_MODE (RW)
 *
 * 00: Normal Mode (one plane mode)
 * 01: Two Plane Mode (Y, UV plane)
 * 10: Y-only Mode, byte sequence as Y0,Y1,Y2,Y3
 * 11: Binary Mode, bit sequence is from LSB to MSB when CR20[BIG_END]=0
 */
#define CAM_CR1_STORAGE_MODE_MASK (0xC00U)
#define CAM_CR1_STORAGE_MODE_SHIFT (10U)
#define CAM_CR1_STORAGE_MODE_SET(x) (((uint32_t)(x) << CAM_CR1_STORAGE_MODE_SHIFT) & CAM_CR1_STORAGE_MODE_MASK)
#define CAM_CR1_STORAGE_MODE_GET(x) (((uint32_t)(x) & CAM_CR1_STORAGE_MODE_MASK) >> CAM_CR1_STORAGE_MODE_SHIFT)

/*
 * COLOR_FORMATS (RW)
 *
 * input color formats:
 * 0010b:24bit:RGB888
 * 0011b:24bit:RGB666
 * 0100b:16bit:RGB565
 * 0101b:16bit:RGB444
 * 0110b:16bit:RGB555
 * 0111b: 16bit: YCbCr422 (Y0 Cb Y1 Cr, each 8-bit)
 * YUV
 * YCrCb
 * Note: YUV420 is not supported.
 * 1000b: 24bit: YUV444
 */
#define CAM_CR1_COLOR_FORMATS_MASK (0x78U)
#define CAM_CR1_COLOR_FORMATS_SHIFT (3U)
#define CAM_CR1_COLOR_FORMATS_SET(x) (((uint32_t)(x) << CAM_CR1_COLOR_FORMATS_SHIFT) & CAM_CR1_COLOR_FORMATS_MASK)
#define CAM_CR1_COLOR_FORMATS_GET(x) (((uint32_t)(x) & CAM_CR1_COLOR_FORMATS_MASK) >> CAM_CR1_COLOR_FORMATS_SHIFT)

/*
 * SENSOR_BIT_WIDTH (RW)
 *
 * the bit width of the sensor
 * 0: 8 bits
 * 1: 10 bits
 * 3:24bits
 * Others: Undefined
 */
#define CAM_CR1_SENSOR_BIT_WIDTH_MASK (0x7U)
#define CAM_CR1_SENSOR_BIT_WIDTH_SHIFT (0U)
#define CAM_CR1_SENSOR_BIT_WIDTH_SET(x) (((uint32_t)(x) << CAM_CR1_SENSOR_BIT_WIDTH_SHIFT) & CAM_CR1_SENSOR_BIT_WIDTH_MASK)
#define CAM_CR1_SENSOR_BIT_WIDTH_GET(x) (((uint32_t)(x) & CAM_CR1_SENSOR_BIT_WIDTH_MASK) >> CAM_CR1_SENSOR_BIT_WIDTH_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * ERR_CL_BWID_CFG_INT_EN (RW)
 *
 * The unsupported color (color_formats[3:0]) and bitwidth (sensor_bit_width[2:0]) configuation interrupt enable
 */
#define CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_MASK (0x2000U)
#define CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_SHIFT (13U)
#define CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_SET(x) (((uint32_t)(x) << CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_SHIFT) & CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_MASK)
#define CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_GET(x) (((uint32_t)(x) & CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_MASK) >> CAM_INT_EN_ERR_CL_BWID_CFG_INT_EN_SHIFT)

/*
 * HIST_DONE_INT_EN (RW)
 *
 * Enable hist done int
 */
#define CAM_INT_EN_HIST_DONE_INT_EN_MASK (0x1000U)
#define CAM_INT_EN_HIST_DONE_INT_EN_SHIFT (12U)
#define CAM_INT_EN_HIST_DONE_INT_EN_SET(x) (((uint32_t)(x) << CAM_INT_EN_HIST_DONE_INT_EN_SHIFT) & CAM_INT_EN_HIST_DONE_INT_EN_MASK)
#define CAM_INT_EN_HIST_DONE_INT_EN_GET(x) (((uint32_t)(x) & CAM_INT_EN_HIST_DONE_INT_EN_MASK) >> CAM_INT_EN_HIST_DONE_INT_EN_SHIFT)

/*
 * HRESP_ERR_EN (RW)
 *
 * Hresponse Error Enable. This bit enables the hresponse error interrupt.
 * 0 Disable hresponse error interrupt
 * 1 Enable hresponse error interrupt
 */
#define CAM_INT_EN_HRESP_ERR_EN_MASK (0x800U)
#define CAM_INT_EN_HRESP_ERR_EN_SHIFT (11U)
#define CAM_INT_EN_HRESP_ERR_EN_SET(x) (((uint32_t)(x) << CAM_INT_EN_HRESP_ERR_EN_SHIFT) & CAM_INT_EN_HRESP_ERR_EN_MASK)
#define CAM_INT_EN_HRESP_ERR_EN_GET(x) (((uint32_t)(x) & CAM_INT_EN_HRESP_ERR_EN_MASK) >> CAM_INT_EN_HRESP_ERR_EN_SHIFT)

/*
 * EOF_INT_EN (RW)
 *
 * End-of-Frame Interrupt Enable. This bit enables and disables the EOF interrupt.
 * 0 EOF interrupt is disabled.
 * 1 EOF interrupt is generated when RX count value is reached.
 */
#define CAM_INT_EN_EOF_INT_EN_MASK (0x200U)
#define CAM_INT_EN_EOF_INT_EN_SHIFT (9U)
#define CAM_INT_EN_EOF_INT_EN_SET(x) (((uint32_t)(x) << CAM_INT_EN_EOF_INT_EN_SHIFT) & CAM_INT_EN_EOF_INT_EN_MASK)
#define CAM_INT_EN_EOF_INT_EN_GET(x) (((uint32_t)(x) & CAM_INT_EN_EOF_INT_EN_MASK) >> CAM_INT_EN_EOF_INT_EN_SHIFT)

/*
 * RF_OR_INTEN (RW)
 *
 * RxFIFO Overrun Interrupt Enable. This bit enables the RX FIFO overrun interrupt.
 * 0 RxFIFO overrun interrupt is disabled
 * 1 RxFIFO overrun interrupt is enabled
 */
#define CAM_INT_EN_RF_OR_INTEN_MASK (0x40U)
#define CAM_INT_EN_RF_OR_INTEN_SHIFT (6U)
#define CAM_INT_EN_RF_OR_INTEN_SET(x) (((uint32_t)(x) << CAM_INT_EN_RF_OR_INTEN_SHIFT) & CAM_INT_EN_RF_OR_INTEN_MASK)
#define CAM_INT_EN_RF_OR_INTEN_GET(x) (((uint32_t)(x) & CAM_INT_EN_RF_OR_INTEN_MASK) >> CAM_INT_EN_RF_OR_INTEN_SHIFT)

/*
 * FB2_DMA_DONE_INTEN (RW)
 *
 * Frame Buffer2 DMA Transfer Done Interrupt Enable. This bit enables the interrupt of Frame Buffer2 DMA
 * transfer done.
 * 0 Frame Buffer2 DMA Transfer Done interrupt disable
 * 1 Frame Buffer2 DMA Transfer Done interrupt enable
 */
#define CAM_INT_EN_FB2_DMA_DONE_INTEN_MASK (0x8U)
#define CAM_INT_EN_FB2_DMA_DONE_INTEN_SHIFT (3U)
#define CAM_INT_EN_FB2_DMA_DONE_INTEN_SET(x) (((uint32_t)(x) << CAM_INT_EN_FB2_DMA_DONE_INTEN_SHIFT) & CAM_INT_EN_FB2_DMA_DONE_INTEN_MASK)
#define CAM_INT_EN_FB2_DMA_DONE_INTEN_GET(x) (((uint32_t)(x) & CAM_INT_EN_FB2_DMA_DONE_INTEN_MASK) >> CAM_INT_EN_FB2_DMA_DONE_INTEN_SHIFT)

/*
 * FB1_DMA_DONE_INTEN (RW)
 *
 * Frame Buffer1 DMA Transfer Done Interrupt Enable. This bit enables the interrupt of Frame Buffer1 DMA
 * transfer done.
 * 0 Frame Buffer1 DMA Transfer Done interrupt disable
 * 1 Frame Buffer1 DMA Transfer Done interrupt enable
 */
#define CAM_INT_EN_FB1_DMA_DONE_INTEN_MASK (0x4U)
#define CAM_INT_EN_FB1_DMA_DONE_INTEN_SHIFT (2U)
#define CAM_INT_EN_FB1_DMA_DONE_INTEN_SET(x) (((uint32_t)(x) << CAM_INT_EN_FB1_DMA_DONE_INTEN_SHIFT) & CAM_INT_EN_FB1_DMA_DONE_INTEN_MASK)
#define CAM_INT_EN_FB1_DMA_DONE_INTEN_GET(x) (((uint32_t)(x) & CAM_INT_EN_FB1_DMA_DONE_INTEN_MASK) >> CAM_INT_EN_FB1_DMA_DONE_INTEN_SHIFT)

/*
 * SOF_INT_EN (RW)
 *
 * Start Of Frame (SOF) Interrupt Enable. This bit enables the SOF interrupt.
 * 0 SOF interrupt disable
 * 1 SOF interrupt enable
 */
#define CAM_INT_EN_SOF_INT_EN_MASK (0x1U)
#define CAM_INT_EN_SOF_INT_EN_SHIFT (0U)
#define CAM_INT_EN_SOF_INT_EN_SET(x) (((uint32_t)(x) << CAM_INT_EN_SOF_INT_EN_SHIFT) & CAM_INT_EN_SOF_INT_EN_MASK)
#define CAM_INT_EN_SOF_INT_EN_GET(x) (((uint32_t)(x) & CAM_INT_EN_SOF_INT_EN_MASK) >> CAM_INT_EN_SOF_INT_EN_SHIFT)

/* Bitfield definition for register: CR2 */
/*
 * FRMCNT_15_0 (RO)
 *
 * Frame Counter. This is a 16-bit Frame Counter
 * (Wraps around automatically after reaching the maximum)
 */
#define CAM_CR2_FRMCNT_15_0_MASK (0xFFFF0000UL)
#define CAM_CR2_FRMCNT_15_0_SHIFT (16U)
#define CAM_CR2_FRMCNT_15_0_GET(x) (((uint32_t)(x) & CAM_CR2_FRMCNT_15_0_MASK) >> CAM_CR2_FRMCNT_15_0_SHIFT)

/*
 * FRMCNT_RST (RW)
 *
 * Frame Count Reset. Resets the Frame Counter.
 * 0 Do not reset
 * 1 Reset frame counter immediately
 */
#define CAM_CR2_FRMCNT_RST_MASK (0x8000U)
#define CAM_CR2_FRMCNT_RST_SHIFT (15U)
#define CAM_CR2_FRMCNT_RST_SET(x) (((uint32_t)(x) << CAM_CR2_FRMCNT_RST_SHIFT) & CAM_CR2_FRMCNT_RST_MASK)
#define CAM_CR2_FRMCNT_RST_GET(x) (((uint32_t)(x) & CAM_CR2_FRMCNT_RST_MASK) >> CAM_CR2_FRMCNT_RST_SHIFT)

/*
 * RXFF_LEVEL (RW)
 *
 * RxFIFO Full Level. When the number of data in RxFIFO reaches this level, a RxFIFO full interrupt is generated, or an RXFIFO DMA request is sent.
 * 000 4 Double words
 * 001 8 Double words
 * 010 16 Double words
 * 011 24 Double words
 * 100 32 Double words
 * 101 48 Double words
 * 110 64 Double words
 * 111 96 Double words
 */
#define CAM_CR2_RXFF_LEVEL_MASK (0xE00U)
#define CAM_CR2_RXFF_LEVEL_SHIFT (9U)
#define CAM_CR2_RXFF_LEVEL_SET(x) (((uint32_t)(x) << CAM_CR2_RXFF_LEVEL_SHIFT) & CAM_CR2_RXFF_LEVEL_MASK)
#define CAM_CR2_RXFF_LEVEL_GET(x) (((uint32_t)(x) & CAM_CR2_RXFF_LEVEL_MASK) >> CAM_CR2_RXFF_LEVEL_SHIFT)

/*
 * DMA_REQ_EN_RFF (RW)
 *
 * DMA Request Enable for RxFIFO. This bit enables the dma request from RxFIFO to the embedded DMA controller.
 * 0 Disable the dma request
 * 1 Enable the dma request. The UV Rx FIFO is only enabled to filling data in 2 plane mode.
 */
#define CAM_CR2_DMA_REQ_EN_RFF_MASK (0x20U)
#define CAM_CR2_DMA_REQ_EN_RFF_SHIFT (5U)
#define CAM_CR2_DMA_REQ_EN_RFF_SET(x) (((uint32_t)(x) << CAM_CR2_DMA_REQ_EN_RFF_SHIFT) & CAM_CR2_DMA_REQ_EN_RFF_MASK)
#define CAM_CR2_DMA_REQ_EN_RFF_GET(x) (((uint32_t)(x) & CAM_CR2_DMA_REQ_EN_RFF_MASK) >> CAM_CR2_DMA_REQ_EN_RFF_SHIFT)

/*
 * CLRBITFORMAT (RW)
 *
 * Input Byte & bit sequence same as OV5640, except for Raw mode. Used only for internal ARGB conversion.
 */
#define CAM_CR2_CLRBITFORMAT_MASK (0xFU)
#define CAM_CR2_CLRBITFORMAT_SHIFT (0U)
#define CAM_CR2_CLRBITFORMAT_SET(x) (((uint32_t)(x) << CAM_CR2_CLRBITFORMAT_SHIFT) & CAM_CR2_CLRBITFORMAT_MASK)
#define CAM_CR2_CLRBITFORMAT_GET(x) (((uint32_t)(x) & CAM_CR2_CLRBITFORMAT_MASK) >> CAM_CR2_CLRBITFORMAT_SHIFT)

/* Bitfield definition for register: STA */
/*
 * ERR_CL_BWID_CFG (W1C)
 *
 * The unsupported color (color_formats[3:0]) and bitwidth (sensor_bit_width[2:0]) configuation found
 */
#define CAM_STA_ERR_CL_BWID_CFG_MASK (0x80000UL)
#define CAM_STA_ERR_CL_BWID_CFG_SHIFT (19U)
#define CAM_STA_ERR_CL_BWID_CFG_SET(x) (((uint32_t)(x) << CAM_STA_ERR_CL_BWID_CFG_SHIFT) & CAM_STA_ERR_CL_BWID_CFG_MASK)
#define CAM_STA_ERR_CL_BWID_CFG_GET(x) (((uint32_t)(x) & CAM_STA_ERR_CL_BWID_CFG_MASK) >> CAM_STA_ERR_CL_BWID_CFG_SHIFT)

/*
 * HIST_DONE (W1C)
 *
 * hist cal done
 */
#define CAM_STA_HIST_DONE_MASK (0x40000UL)
#define CAM_STA_HIST_DONE_SHIFT (18U)
#define CAM_STA_HIST_DONE_SET(x) (((uint32_t)(x) << CAM_STA_HIST_DONE_SHIFT) & CAM_STA_HIST_DONE_MASK)
#define CAM_STA_HIST_DONE_GET(x) (((uint32_t)(x) & CAM_STA_HIST_DONE_MASK) >> CAM_STA_HIST_DONE_SHIFT)

/*
 * RF_OR_INT (W1C)
 *
 * RxFIFO Overrun Interrupt Status. Indicates the overflow status of the RxFIFO register. (Cleared by writing
 * 1)
 * 0 RXFIFO has not overflowed.
 * 1 RXFIFO has overflowed.
 */
#define CAM_STA_RF_OR_INT_MASK (0x2000U)
#define CAM_STA_RF_OR_INT_SHIFT (13U)
#define CAM_STA_RF_OR_INT_SET(x) (((uint32_t)(x) << CAM_STA_RF_OR_INT_SHIFT) & CAM_STA_RF_OR_INT_MASK)
#define CAM_STA_RF_OR_INT_GET(x) (((uint32_t)(x) & CAM_STA_RF_OR_INT_MASK) >> CAM_STA_RF_OR_INT_SHIFT)

/*
 * DMA_TSF_DONE_FB2 (W1C)
 *
 * DMA Transfer Done in Frame Buffer2. Indicates that the DMA transfer from RxFIFO to Frame Buffer2 is completed. It can trigger an interrupt if the corresponding enable bit is set in CAM_CR1. This bit can be cleared by by writing 1 or reflashing the RxFIFO dma controller in CAM_CR3. (Cleared by writing 1)
 * 0 DMA transfer is not completed.
 * 1 DMA transfer is completed.
 */
#define CAM_STA_DMA_TSF_DONE_FB2_MASK (0x400U)
#define CAM_STA_DMA_TSF_DONE_FB2_SHIFT (10U)
#define CAM_STA_DMA_TSF_DONE_FB2_SET(x) (((uint32_t)(x) << CAM_STA_DMA_TSF_DONE_FB2_SHIFT) & CAM_STA_DMA_TSF_DONE_FB2_MASK)
#define CAM_STA_DMA_TSF_DONE_FB2_GET(x) (((uint32_t)(x) & CAM_STA_DMA_TSF_DONE_FB2_MASK) >> CAM_STA_DMA_TSF_DONE_FB2_SHIFT)

/*
 * DMA_TSF_DONE_FB1 (W1C)
 *
 * DMA Transfer Done in Frame Buffer1. Indicates that the DMA transfer from RxFIFO to Frame Buffer1 is completed. It can trigger an interrupt if the corresponding enable bit is set in CAM_CR1. This bit can be cleared by by writing 1 or reflashing the RxFIFO dma controller in CAM_CR3. (Cleared by writing 1)
 * 0 DMA transfer is not completed.
 * 1 DMA transfer is completed.
 */
#define CAM_STA_DMA_TSF_DONE_FB1_MASK (0x200U)
#define CAM_STA_DMA_TSF_DONE_FB1_SHIFT (9U)
#define CAM_STA_DMA_TSF_DONE_FB1_SET(x) (((uint32_t)(x) << CAM_STA_DMA_TSF_DONE_FB1_SHIFT) & CAM_STA_DMA_TSF_DONE_FB1_MASK)
#define CAM_STA_DMA_TSF_DONE_FB1_GET(x) (((uint32_t)(x) & CAM_STA_DMA_TSF_DONE_FB1_MASK) >> CAM_STA_DMA_TSF_DONE_FB1_SHIFT)

/*
 * EOF_INT (W1C)
 *
 * End of Frame (EOF) Interrupt Status. Indicates when EOF is detected. (Cleared by writing 1)
 * 0 EOF is not detected.
 * 1 EOF is detected.
 */
#define CAM_STA_EOF_INT_MASK (0x80U)
#define CAM_STA_EOF_INT_SHIFT (7U)
#define CAM_STA_EOF_INT_SET(x) (((uint32_t)(x) << CAM_STA_EOF_INT_SHIFT) & CAM_STA_EOF_INT_MASK)
#define CAM_STA_EOF_INT_GET(x) (((uint32_t)(x) & CAM_STA_EOF_INT_MASK) >> CAM_STA_EOF_INT_SHIFT)

/*
 * SOF_INT (W1C)
 *
 * Start of Frame Interrupt Status. Indicates when SOF is detected. (Cleared by writing 1)
 * 0 SOF is not detected.
 * 1 SOF is detected.
 */
#define CAM_STA_SOF_INT_MASK (0x40U)
#define CAM_STA_SOF_INT_SHIFT (6U)
#define CAM_STA_SOF_INT_SET(x) (((uint32_t)(x) << CAM_STA_SOF_INT_SHIFT) & CAM_STA_SOF_INT_MASK)
#define CAM_STA_SOF_INT_GET(x) (((uint32_t)(x) & CAM_STA_SOF_INT_MASK) >> CAM_STA_SOF_INT_SHIFT)

/*
 * HRESP_ERR_INT (W1C)
 *
 * Hresponse Error Interrupt Status. Indicates that a hresponse error has been detected. (Cleared by writing
 * 1)
 * 0 No hresponse error.
 * 1 Hresponse error is detected.
 */
#define CAM_STA_HRESP_ERR_INT_MASK (0x4U)
#define CAM_STA_HRESP_ERR_INT_SHIFT (2U)
#define CAM_STA_HRESP_ERR_INT_SET(x) (((uint32_t)(x) << CAM_STA_HRESP_ERR_INT_SHIFT) & CAM_STA_HRESP_ERR_INT_MASK)
#define CAM_STA_HRESP_ERR_INT_GET(x) (((uint32_t)(x) & CAM_STA_HRESP_ERR_INT_MASK) >> CAM_STA_HRESP_ERR_INT_SHIFT)

/* Bitfield definition for register: DMASA_FB1 */
/*
 * PTR (RW)
 *
 * DMA Start Address in Frame Buffer1. Indicates the start address to write data. The embedded DMA controller will read data from RxFIFO and write it from this address through AHB bus. The address should be double words aligned.
 * In Two-Plane Mode, Y buffer1
 */
#define CAM_DMASA_FB1_PTR_MASK (0xFFFFFFFCUL)
#define CAM_DMASA_FB1_PTR_SHIFT (2U)
#define CAM_DMASA_FB1_PTR_SET(x) (((uint32_t)(x) << CAM_DMASA_FB1_PTR_SHIFT) & CAM_DMASA_FB1_PTR_MASK)
#define CAM_DMASA_FB1_PTR_GET(x) (((uint32_t)(x) & CAM_DMASA_FB1_PTR_MASK) >> CAM_DMASA_FB1_PTR_SHIFT)

/* Bitfield definition for register: DMASA_FB2 */
/*
 * PTR (RW)
 *
 * DMA Start Address in Frame Buffer2. Indicates the start address to write data. The embedded DMA controller will read data from RxFIFO and write it from this address through AHB bus. The address should be double words aligned.
 * In Two-Plane Mode, Y buffer2
 */
#define CAM_DMASA_FB2_PTR_MASK (0xFFFFFFFCUL)
#define CAM_DMASA_FB2_PTR_SHIFT (2U)
#define CAM_DMASA_FB2_PTR_SET(x) (((uint32_t)(x) << CAM_DMASA_FB2_PTR_SHIFT) & CAM_DMASA_FB2_PTR_MASK)
#define CAM_DMASA_FB2_PTR_GET(x) (((uint32_t)(x) & CAM_DMASA_FB2_PTR_MASK) >> CAM_DMASA_FB2_PTR_SHIFT)

/* Bitfield definition for register: BUF_PARA */
/*
 * LINEBSP_STRIDE (RW)
 *
 * Line Blank Space Stride. Indicates the space between the end of line image storage and the start of a new line storage in the frame buffer.
 * The width of the line storage in frame buffer(in double words) minus the width of the image(in double words) is the stride. The stride should be double words aligned. The embedded DMA controller will skip the stride before starting to write the next row of the image.
 */
#define CAM_BUF_PARA_LINEBSP_STRIDE_MASK (0xFFFFU)
#define CAM_BUF_PARA_LINEBSP_STRIDE_SHIFT (0U)
#define CAM_BUF_PARA_LINEBSP_STRIDE_SET(x) (((uint32_t)(x) << CAM_BUF_PARA_LINEBSP_STRIDE_SHIFT) & CAM_BUF_PARA_LINEBSP_STRIDE_MASK)
#define CAM_BUF_PARA_LINEBSP_STRIDE_GET(x) (((uint32_t)(x) & CAM_BUF_PARA_LINEBSP_STRIDE_MASK) >> CAM_BUF_PARA_LINEBSP_STRIDE_SHIFT)

/* Bitfield definition for register: IDEAL_WN_SIZE */
/*
 * HEIGHT (RW)
 *
 * Image Height. Indicates how many active pixels in a column of the image from the sensor.
 */
#define CAM_IDEAL_WN_SIZE_HEIGHT_MASK (0xFFFF0000UL)
#define CAM_IDEAL_WN_SIZE_HEIGHT_SHIFT (16U)
#define CAM_IDEAL_WN_SIZE_HEIGHT_SET(x) (((uint32_t)(x) << CAM_IDEAL_WN_SIZE_HEIGHT_SHIFT) & CAM_IDEAL_WN_SIZE_HEIGHT_MASK)
#define CAM_IDEAL_WN_SIZE_HEIGHT_GET(x) (((uint32_t)(x) & CAM_IDEAL_WN_SIZE_HEIGHT_MASK) >> CAM_IDEAL_WN_SIZE_HEIGHT_SHIFT)

/*
 * WIDTH (RW)
 *
 * Image Width. Indicates how many active pixels in a line of the image from the sensor.
 * The number of bytes to be transferred is re-calculated automatically in hardware based on cr1[color_ext] and cr1[store_mode]. Default value is 2*pixel number.
 * As the input data from the sensor is 8-bit/pixel format, the IMAGE_WIDTH should be a multiple of 8 pixels.
 */
#define CAM_IDEAL_WN_SIZE_WIDTH_MASK (0xFFFFU)
#define CAM_IDEAL_WN_SIZE_WIDTH_SHIFT (0U)
#define CAM_IDEAL_WN_SIZE_WIDTH_SET(x) (((uint32_t)(x) << CAM_IDEAL_WN_SIZE_WIDTH_SHIFT) & CAM_IDEAL_WN_SIZE_WIDTH_MASK)
#define CAM_IDEAL_WN_SIZE_WIDTH_GET(x) (((uint32_t)(x) & CAM_IDEAL_WN_SIZE_WIDTH_MASK) >> CAM_IDEAL_WN_SIZE_WIDTH_SHIFT)

/* Bitfield definition for register: CR18 */
/*
 * CAM_ENABLE (RW)
 *
 * CAM global enable signal. Only when this bit is 1, CAM can start to receive the data and store to memory.
 */
#define CAM_CR18_CAM_ENABLE_MASK (0x80000000UL)
#define CAM_CR18_CAM_ENABLE_SHIFT (31U)
#define CAM_CR18_CAM_ENABLE_SET(x) (((uint32_t)(x) << CAM_CR18_CAM_ENABLE_SHIFT) & CAM_CR18_CAM_ENABLE_MASK)
#define CAM_CR18_CAM_ENABLE_GET(x) (((uint32_t)(x) & CAM_CR18_CAM_ENABLE_MASK) >> CAM_CR18_CAM_ENABLE_SHIFT)

/*
 * AWQOS (RW)
 *
 * AWQOS for bus fabric arbitration
 */
#define CAM_CR18_AWQOS_MASK (0x780U)
#define CAM_CR18_AWQOS_SHIFT (7U)
#define CAM_CR18_AWQOS_SET(x) (((uint32_t)(x) << CAM_CR18_AWQOS_SHIFT) & CAM_CR18_AWQOS_MASK)
#define CAM_CR18_AWQOS_GET(x) (((uint32_t)(x) & CAM_CR18_AWQOS_MASK) >> CAM_CR18_AWQOS_SHIFT)

/* Bitfield definition for register: DMASA_UV1 */
/*
 * PTR (RW)
 *
 * Two Plane UV Buffer Start Address 1
 */
#define CAM_DMASA_UV1_PTR_MASK (0xFFFFFFFCUL)
#define CAM_DMASA_UV1_PTR_SHIFT (2U)
#define CAM_DMASA_UV1_PTR_SET(x) (((uint32_t)(x) << CAM_DMASA_UV1_PTR_SHIFT) & CAM_DMASA_UV1_PTR_MASK)
#define CAM_DMASA_UV1_PTR_GET(x) (((uint32_t)(x) & CAM_DMASA_UV1_PTR_MASK) >> CAM_DMASA_UV1_PTR_SHIFT)

/* Bitfield definition for register: DMASA_UV2 */
/*
 * PTR (RW)
 *
 * Two Plane UV Buffer Start Address 2
 */
#define CAM_DMASA_UV2_PTR_MASK (0xFFFFFFFCUL)
#define CAM_DMASA_UV2_PTR_SHIFT (2U)
#define CAM_DMASA_UV2_PTR_SET(x) (((uint32_t)(x) << CAM_DMASA_UV2_PTR_SHIFT) & CAM_DMASA_UV2_PTR_MASK)
#define CAM_DMASA_UV2_PTR_GET(x) (((uint32_t)(x) & CAM_DMASA_UV2_PTR_MASK) >> CAM_DMASA_UV2_PTR_SHIFT)

/* Bitfield definition for register: CR20 */
/*
 * BINARY_EN (RW)
 *
 * binary picture output enable
 */
#define CAM_CR20_BINARY_EN_MASK (0x80000000UL)
#define CAM_CR20_BINARY_EN_SHIFT (31U)
#define CAM_CR20_BINARY_EN_SET(x) (((uint32_t)(x) << CAM_CR20_BINARY_EN_SHIFT) & CAM_CR20_BINARY_EN_MASK)
#define CAM_CR20_BINARY_EN_GET(x) (((uint32_t)(x) & CAM_CR20_BINARY_EN_MASK) >> CAM_CR20_BINARY_EN_SHIFT)

/*
 * HISTOGRAM_EN (RW)
 *
 * histogarm enable
 */
#define CAM_CR20_HISTOGRAM_EN_MASK (0x40000000UL)
#define CAM_CR20_HISTOGRAM_EN_SHIFT (30U)
#define CAM_CR20_HISTOGRAM_EN_SET(x) (((uint32_t)(x) << CAM_CR20_HISTOGRAM_EN_SHIFT) & CAM_CR20_HISTOGRAM_EN_MASK)
#define CAM_CR20_HISTOGRAM_EN_GET(x) (((uint32_t)(x) & CAM_CR20_HISTOGRAM_EN_MASK) >> CAM_CR20_HISTOGRAM_EN_SHIFT)

/*
 * BIG_END (RW)
 *
 * Asserted when binary output is in big-endian type, which mean the right most data is at the LSBs. Take function only inside the 32-bit word.
 */
#define CAM_CR20_BIG_END_MASK (0x100U)
#define CAM_CR20_BIG_END_SHIFT (8U)
#define CAM_CR20_BIG_END_SET(x) (((uint32_t)(x) << CAM_CR20_BIG_END_SHIFT) & CAM_CR20_BIG_END_MASK)
#define CAM_CR20_BIG_END_GET(x) (((uint32_t)(x) & CAM_CR20_BIG_END_MASK) >> CAM_CR20_BIG_END_SHIFT)

/*
 * THRESHOLD (RW)
 *
 * Threshold to generate binary color. Bin 1 is output if the pixel is greater than the threshold.
 */
#define CAM_CR20_THRESHOLD_MASK (0xFFU)
#define CAM_CR20_THRESHOLD_SHIFT (0U)
#define CAM_CR20_THRESHOLD_SET(x) (((uint32_t)(x) << CAM_CR20_THRESHOLD_SHIFT) & CAM_CR20_THRESHOLD_MASK)
#define CAM_CR20_THRESHOLD_GET(x) (((uint32_t)(x) & CAM_CR20_THRESHOLD_MASK) >> CAM_CR20_THRESHOLD_SHIFT)

/* Bitfield definition for register: CSC_COEF0 */
/*
 * YCBCR_MODE (RW)
 *
 * This bit changes the behavior when performing U/V converting.
 * 0b - Converting YUV to RGB data
 * 1b - Converting YCbCr to RGB data
 */
#define CAM_CSC_COEF0_YCBCR_MODE_MASK (0x80000000UL)
#define CAM_CSC_COEF0_YCBCR_MODE_SHIFT (31U)
#define CAM_CSC_COEF0_YCBCR_MODE_SET(x) (((uint32_t)(x) << CAM_CSC_COEF0_YCBCR_MODE_SHIFT) & CAM_CSC_COEF0_YCBCR_MODE_MASK)
#define CAM_CSC_COEF0_YCBCR_MODE_GET(x) (((uint32_t)(x) & CAM_CSC_COEF0_YCBCR_MODE_MASK) >> CAM_CSC_COEF0_YCBCR_MODE_SHIFT)

/*
 * ENABLE (RW)
 *
 * Enable the CSC unit
 * 0b - The CSC is bypassed and the input pixels are RGB data already
 * 1b - The CSC is enabled and the pixels will be converted to RGB data
 */
#define CAM_CSC_COEF0_ENABLE_MASK (0x40000000UL)
#define CAM_CSC_COEF0_ENABLE_SHIFT (30U)
#define CAM_CSC_COEF0_ENABLE_SET(x) (((uint32_t)(x) << CAM_CSC_COEF0_ENABLE_SHIFT) & CAM_CSC_COEF0_ENABLE_MASK)
#define CAM_CSC_COEF0_ENABLE_GET(x) (((uint32_t)(x) & CAM_CSC_COEF0_ENABLE_MASK) >> CAM_CSC_COEF0_ENABLE_SHIFT)

/*
 * C0 (RW)
 *
 * Two's compliment Y multiplier coefficient. YUV=0x100 (1.000) YCbCr=0x12A (1.164)
 */
#define CAM_CSC_COEF0_C0_MASK (0x1FFC0000UL)
#define CAM_CSC_COEF0_C0_SHIFT (18U)
#define CAM_CSC_COEF0_C0_SET(x) (((uint32_t)(x) << CAM_CSC_COEF0_C0_SHIFT) & CAM_CSC_COEF0_C0_MASK)
#define CAM_CSC_COEF0_C0_GET(x) (((uint32_t)(x) & CAM_CSC_COEF0_C0_MASK) >> CAM_CSC_COEF0_C0_SHIFT)

/*
 * UV_OFFSET (RW)
 *
 * Two's compliment phase offset implicit for CbCr data. Generally used for YCbCr to RGB conversion.
 * YCbCr=0x180, YUV=0x000 (typically -128 or 0x180 to indicate normalized -0.5 to 0.5 range).
 */
#define CAM_CSC_COEF0_UV_OFFSET_MASK (0x3FE00UL)
#define CAM_CSC_COEF0_UV_OFFSET_SHIFT (9U)
#define CAM_CSC_COEF0_UV_OFFSET_SET(x) (((uint32_t)(x) << CAM_CSC_COEF0_UV_OFFSET_SHIFT) & CAM_CSC_COEF0_UV_OFFSET_MASK)
#define CAM_CSC_COEF0_UV_OFFSET_GET(x) (((uint32_t)(x) & CAM_CSC_COEF0_UV_OFFSET_MASK) >> CAM_CSC_COEF0_UV_OFFSET_SHIFT)

/*
 * Y_OFFSET (RW)
 *
 * Two's compliment amplitude offset implicit in the Y data. For YUV, this is typically 0 and for YCbCr, this is
 * typically -16 (0x1F0).
 */
#define CAM_CSC_COEF0_Y_OFFSET_MASK (0x1FFU)
#define CAM_CSC_COEF0_Y_OFFSET_SHIFT (0U)
#define CAM_CSC_COEF0_Y_OFFSET_SET(x) (((uint32_t)(x) << CAM_CSC_COEF0_Y_OFFSET_SHIFT) & CAM_CSC_COEF0_Y_OFFSET_MASK)
#define CAM_CSC_COEF0_Y_OFFSET_GET(x) (((uint32_t)(x) & CAM_CSC_COEF0_Y_OFFSET_MASK) >> CAM_CSC_COEF0_Y_OFFSET_SHIFT)

/* Bitfield definition for register: CSC_COEF1 */
/*
 * C1 (RW)
 *
 * Two's compliment Red V/Cr multiplier coefficient. YUV=0x123 (1.140) YCbCr=0x198 (1.596).
 */
#define CAM_CSC_COEF1_C1_MASK (0x7FF0000UL)
#define CAM_CSC_COEF1_C1_SHIFT (16U)
#define CAM_CSC_COEF1_C1_SET(x) (((uint32_t)(x) << CAM_CSC_COEF1_C1_SHIFT) & CAM_CSC_COEF1_C1_MASK)
#define CAM_CSC_COEF1_C1_GET(x) (((uint32_t)(x) & CAM_CSC_COEF1_C1_MASK) >> CAM_CSC_COEF1_C1_SHIFT)

/*
 * C4 (RW)
 *
 * Two's compliment Blue U/Cb multiplier coefficient. YUV=0x208 (2.032) YCbCr=0x204 (2.017).
 */
#define CAM_CSC_COEF1_C4_MASK (0x7FFU)
#define CAM_CSC_COEF1_C4_SHIFT (0U)
#define CAM_CSC_COEF1_C4_SET(x) (((uint32_t)(x) << CAM_CSC_COEF1_C4_SHIFT) & CAM_CSC_COEF1_C4_MASK)
#define CAM_CSC_COEF1_C4_GET(x) (((uint32_t)(x) & CAM_CSC_COEF1_C4_MASK) >> CAM_CSC_COEF1_C4_SHIFT)

/* Bitfield definition for register: CSC_COEF2 */
/*
 * C2 (RW)
 *
 * Two's compliment Green V/Cr multiplier coefficient. YUV=0x76B (-0.581) YCbCr=0x730 (-0.813).
 */
#define CAM_CSC_COEF2_C2_MASK (0x7FF0000UL)
#define CAM_CSC_COEF2_C2_SHIFT (16U)
#define CAM_CSC_COEF2_C2_SET(x) (((uint32_t)(x) << CAM_CSC_COEF2_C2_SHIFT) & CAM_CSC_COEF2_C2_MASK)
#define CAM_CSC_COEF2_C2_GET(x) (((uint32_t)(x) & CAM_CSC_COEF2_C2_MASK) >> CAM_CSC_COEF2_C2_SHIFT)

/*
 * C3 (RW)
 *
 * Two's compliment Green U/Cb multiplier coefficient. YUV=0x79C (-0.394) YCbCr=0x79C (-0.392).
 */
#define CAM_CSC_COEF2_C3_MASK (0x7FFU)
#define CAM_CSC_COEF2_C3_SHIFT (0U)
#define CAM_CSC_COEF2_C3_SET(x) (((uint32_t)(x) << CAM_CSC_COEF2_C3_SHIFT) & CAM_CSC_COEF2_C3_MASK)
#define CAM_CSC_COEF2_C3_GET(x) (((uint32_t)(x) & CAM_CSC_COEF2_C3_MASK) >> CAM_CSC_COEF2_C3_SHIFT)

/* Bitfield definition for register: CLRKEY_LOW */
/*
 * LIMIT (RW)
 *
 * Low range of color key applied to PS buffer. To disable PS colorkeying, set the low colorkey to 0xFFFFFF and the high colorkey to 0x000000.
 */
#define CAM_CLRKEY_LOW_LIMIT_MASK (0xFFFFFFUL)
#define CAM_CLRKEY_LOW_LIMIT_SHIFT (0U)
#define CAM_CLRKEY_LOW_LIMIT_SET(x) (((uint32_t)(x) << CAM_CLRKEY_LOW_LIMIT_SHIFT) & CAM_CLRKEY_LOW_LIMIT_MASK)
#define CAM_CLRKEY_LOW_LIMIT_GET(x) (((uint32_t)(x) & CAM_CLRKEY_LOW_LIMIT_MASK) >> CAM_CLRKEY_LOW_LIMIT_SHIFT)

/* Bitfield definition for register: CLRKEY_HIGH */
/*
 * LIMIT (RW)
 *
 * Low range of color key applied to PS buffer. To disable PS colorkeying, set the low colorkey to 0xFFFFFF and the high colorkey to 0x000000.
 */
#define CAM_CLRKEY_HIGH_LIMIT_MASK (0xFFFFFFUL)
#define CAM_CLRKEY_HIGH_LIMIT_SHIFT (0U)
#define CAM_CLRKEY_HIGH_LIMIT_SET(x) (((uint32_t)(x) << CAM_CLRKEY_HIGH_LIMIT_SHIFT) & CAM_CLRKEY_HIGH_LIMIT_MASK)
#define CAM_CLRKEY_HIGH_LIMIT_GET(x) (((uint32_t)(x) & CAM_CLRKEY_HIGH_LIMIT_MASK) >> CAM_CLRKEY_HIGH_LIMIT_SHIFT)

/* Bitfield definition for register array: HISTOGRAM_FIFO */
/*
 * HIST_Y (RO)
 *
 * the appearance of bin x (x=(address-DATA0)/4)
 */
#define CAM_HISTOGRAM_FIFO_HIST_Y_MASK (0xFFFFFFUL)
#define CAM_HISTOGRAM_FIFO_HIST_Y_SHIFT (0U)
#define CAM_HISTOGRAM_FIFO_HIST_Y_GET(x) (((uint32_t)(x) & CAM_HISTOGRAM_FIFO_HIST_Y_MASK) >> CAM_HISTOGRAM_FIFO_HIST_Y_SHIFT)



/* HISTOGRAM_FIFO register group index macro definition */
#define CAM_HISTOGRAM_FIFO_DATA0 (0UL)
#define CAM_HISTOGRAM_FIFO_DATA1 (1UL)
#define CAM_HISTOGRAM_FIFO_DATA2 (2UL)
#define CAM_HISTOGRAM_FIFO_DATA3 (3UL)
#define CAM_HISTOGRAM_FIFO_DATA4 (4UL)
#define CAM_HISTOGRAM_FIFO_DATA5 (5UL)
#define CAM_HISTOGRAM_FIFO_DATA6 (6UL)
#define CAM_HISTOGRAM_FIFO_DATA7 (7UL)
#define CAM_HISTOGRAM_FIFO_DATA8 (8UL)
#define CAM_HISTOGRAM_FIFO_DATA9 (9UL)
#define CAM_HISTOGRAM_FIFO_DATA10 (10UL)
#define CAM_HISTOGRAM_FIFO_DATA11 (11UL)
#define CAM_HISTOGRAM_FIFO_DATA12 (12UL)
#define CAM_HISTOGRAM_FIFO_DATA13 (13UL)
#define CAM_HISTOGRAM_FIFO_DATA14 (14UL)
#define CAM_HISTOGRAM_FIFO_DATA15 (15UL)
#define CAM_HISTOGRAM_FIFO_DATA16 (16UL)
#define CAM_HISTOGRAM_FIFO_DATA17 (17UL)
#define CAM_HISTOGRAM_FIFO_DATA18 (18UL)
#define CAM_HISTOGRAM_FIFO_DATA19 (19UL)
#define CAM_HISTOGRAM_FIFO_DATA20 (20UL)
#define CAM_HISTOGRAM_FIFO_DATA21 (21UL)
#define CAM_HISTOGRAM_FIFO_DATA22 (22UL)
#define CAM_HISTOGRAM_FIFO_DATA23 (23UL)
#define CAM_HISTOGRAM_FIFO_DATA24 (24UL)
#define CAM_HISTOGRAM_FIFO_DATA25 (25UL)
#define CAM_HISTOGRAM_FIFO_DATA26 (26UL)
#define CAM_HISTOGRAM_FIFO_DATA27 (27UL)
#define CAM_HISTOGRAM_FIFO_DATA28 (28UL)
#define CAM_HISTOGRAM_FIFO_DATA29 (29UL)
#define CAM_HISTOGRAM_FIFO_DATA30 (30UL)
#define CAM_HISTOGRAM_FIFO_DATA31 (31UL)
#define CAM_HISTOGRAM_FIFO_DATA32 (32UL)
#define CAM_HISTOGRAM_FIFO_DATA33 (33UL)
#define CAM_HISTOGRAM_FIFO_DATA34 (34UL)
#define CAM_HISTOGRAM_FIFO_DATA35 (35UL)
#define CAM_HISTOGRAM_FIFO_DATA36 (36UL)
#define CAM_HISTOGRAM_FIFO_DATA37 (37UL)
#define CAM_HISTOGRAM_FIFO_DATA38 (38UL)
#define CAM_HISTOGRAM_FIFO_DATA39 (39UL)
#define CAM_HISTOGRAM_FIFO_DATA40 (40UL)
#define CAM_HISTOGRAM_FIFO_DATA41 (41UL)
#define CAM_HISTOGRAM_FIFO_DATA42 (42UL)
#define CAM_HISTOGRAM_FIFO_DATA43 (43UL)
#define CAM_HISTOGRAM_FIFO_DATA44 (44UL)
#define CAM_HISTOGRAM_FIFO_DATA45 (45UL)
#define CAM_HISTOGRAM_FIFO_DATA46 (46UL)
#define CAM_HISTOGRAM_FIFO_DATA47 (47UL)
#define CAM_HISTOGRAM_FIFO_DATA48 (48UL)
#define CAM_HISTOGRAM_FIFO_DATA49 (49UL)
#define CAM_HISTOGRAM_FIFO_DATA50 (50UL)
#define CAM_HISTOGRAM_FIFO_DATA51 (51UL)
#define CAM_HISTOGRAM_FIFO_DATA52 (52UL)
#define CAM_HISTOGRAM_FIFO_DATA53 (53UL)
#define CAM_HISTOGRAM_FIFO_DATA54 (54UL)
#define CAM_HISTOGRAM_FIFO_DATA55 (55UL)
#define CAM_HISTOGRAM_FIFO_DATA56 (56UL)
#define CAM_HISTOGRAM_FIFO_DATA57 (57UL)
#define CAM_HISTOGRAM_FIFO_DATA58 (58UL)
#define CAM_HISTOGRAM_FIFO_DATA59 (59UL)
#define CAM_HISTOGRAM_FIFO_DATA60 (60UL)
#define CAM_HISTOGRAM_FIFO_DATA61 (61UL)
#define CAM_HISTOGRAM_FIFO_DATA62 (62UL)
#define CAM_HISTOGRAM_FIFO_DATA63 (63UL)
#define CAM_HISTOGRAM_FIFO_DATA64 (64UL)
#define CAM_HISTOGRAM_FIFO_DATA65 (65UL)
#define CAM_HISTOGRAM_FIFO_DATA66 (66UL)
#define CAM_HISTOGRAM_FIFO_DATA67 (67UL)
#define CAM_HISTOGRAM_FIFO_DATA68 (68UL)
#define CAM_HISTOGRAM_FIFO_DATA69 (69UL)
#define CAM_HISTOGRAM_FIFO_DATA70 (70UL)
#define CAM_HISTOGRAM_FIFO_DATA71 (71UL)
#define CAM_HISTOGRAM_FIFO_DATA72 (72UL)
#define CAM_HISTOGRAM_FIFO_DATA73 (73UL)
#define CAM_HISTOGRAM_FIFO_DATA74 (74UL)
#define CAM_HISTOGRAM_FIFO_DATA75 (75UL)
#define CAM_HISTOGRAM_FIFO_DATA76 (76UL)
#define CAM_HISTOGRAM_FIFO_DATA77 (77UL)
#define CAM_HISTOGRAM_FIFO_DATA78 (78UL)
#define CAM_HISTOGRAM_FIFO_DATA79 (79UL)
#define CAM_HISTOGRAM_FIFO_DATA80 (80UL)
#define CAM_HISTOGRAM_FIFO_DATA81 (81UL)
#define CAM_HISTOGRAM_FIFO_DATA82 (82UL)
#define CAM_HISTOGRAM_FIFO_DATA83 (83UL)
#define CAM_HISTOGRAM_FIFO_DATA84 (84UL)
#define CAM_HISTOGRAM_FIFO_DATA85 (85UL)
#define CAM_HISTOGRAM_FIFO_DATA86 (86UL)
#define CAM_HISTOGRAM_FIFO_DATA87 (87UL)
#define CAM_HISTOGRAM_FIFO_DATA88 (88UL)
#define CAM_HISTOGRAM_FIFO_DATA89 (89UL)
#define CAM_HISTOGRAM_FIFO_DATA90 (90UL)
#define CAM_HISTOGRAM_FIFO_DATA91 (91UL)
#define CAM_HISTOGRAM_FIFO_DATA92 (92UL)
#define CAM_HISTOGRAM_FIFO_DATA93 (93UL)
#define CAM_HISTOGRAM_FIFO_DATA94 (94UL)
#define CAM_HISTOGRAM_FIFO_DATA95 (95UL)
#define CAM_HISTOGRAM_FIFO_DATA96 (96UL)
#define CAM_HISTOGRAM_FIFO_DATA97 (97UL)
#define CAM_HISTOGRAM_FIFO_DATA98 (98UL)
#define CAM_HISTOGRAM_FIFO_DATA99 (99UL)
#define CAM_HISTOGRAM_FIFO_DATA100 (100UL)
#define CAM_HISTOGRAM_FIFO_DATA101 (101UL)
#define CAM_HISTOGRAM_FIFO_DATA102 (102UL)
#define CAM_HISTOGRAM_FIFO_DATA103 (103UL)
#define CAM_HISTOGRAM_FIFO_DATA104 (104UL)
#define CAM_HISTOGRAM_FIFO_DATA105 (105UL)
#define CAM_HISTOGRAM_FIFO_DATA106 (106UL)
#define CAM_HISTOGRAM_FIFO_DATA107 (107UL)
#define CAM_HISTOGRAM_FIFO_DATA108 (108UL)
#define CAM_HISTOGRAM_FIFO_DATA109 (109UL)
#define CAM_HISTOGRAM_FIFO_DATA110 (110UL)
#define CAM_HISTOGRAM_FIFO_DATA111 (111UL)
#define CAM_HISTOGRAM_FIFO_DATA112 (112UL)
#define CAM_HISTOGRAM_FIFO_DATA113 (113UL)
#define CAM_HISTOGRAM_FIFO_DATA114 (114UL)
#define CAM_HISTOGRAM_FIFO_DATA115 (115UL)
#define CAM_HISTOGRAM_FIFO_DATA116 (116UL)
#define CAM_HISTOGRAM_FIFO_DATA117 (117UL)
#define CAM_HISTOGRAM_FIFO_DATA118 (118UL)
#define CAM_HISTOGRAM_FIFO_DATA119 (119UL)
#define CAM_HISTOGRAM_FIFO_DATA120 (120UL)
#define CAM_HISTOGRAM_FIFO_DATA121 (121UL)
#define CAM_HISTOGRAM_FIFO_DATA122 (122UL)
#define CAM_HISTOGRAM_FIFO_DATA123 (123UL)
#define CAM_HISTOGRAM_FIFO_DATA124 (124UL)
#define CAM_HISTOGRAM_FIFO_DATA125 (125UL)
#define CAM_HISTOGRAM_FIFO_DATA126 (126UL)
#define CAM_HISTOGRAM_FIFO_DATA127 (127UL)
#define CAM_HISTOGRAM_FIFO_DATA128 (128UL)
#define CAM_HISTOGRAM_FIFO_DATA129 (129UL)
#define CAM_HISTOGRAM_FIFO_DATA130 (130UL)
#define CAM_HISTOGRAM_FIFO_DATA131 (131UL)
#define CAM_HISTOGRAM_FIFO_DATA132 (132UL)
#define CAM_HISTOGRAM_FIFO_DATA133 (133UL)
#define CAM_HISTOGRAM_FIFO_DATA134 (134UL)
#define CAM_HISTOGRAM_FIFO_DATA135 (135UL)
#define CAM_HISTOGRAM_FIFO_DATA136 (136UL)
#define CAM_HISTOGRAM_FIFO_DATA137 (137UL)
#define CAM_HISTOGRAM_FIFO_DATA138 (138UL)
#define CAM_HISTOGRAM_FIFO_DATA139 (139UL)
#define CAM_HISTOGRAM_FIFO_DATA140 (140UL)
#define CAM_HISTOGRAM_FIFO_DATA141 (141UL)
#define CAM_HISTOGRAM_FIFO_DATA142 (142UL)
#define CAM_HISTOGRAM_FIFO_DATA143 (143UL)
#define CAM_HISTOGRAM_FIFO_DATA144 (144UL)
#define CAM_HISTOGRAM_FIFO_DATA145 (145UL)
#define CAM_HISTOGRAM_FIFO_DATA146 (146UL)
#define CAM_HISTOGRAM_FIFO_DATA147 (147UL)
#define CAM_HISTOGRAM_FIFO_DATA148 (148UL)
#define CAM_HISTOGRAM_FIFO_DATA149 (149UL)
#define CAM_HISTOGRAM_FIFO_DATA150 (150UL)
#define CAM_HISTOGRAM_FIFO_DATA151 (151UL)
#define CAM_HISTOGRAM_FIFO_DATA152 (152UL)
#define CAM_HISTOGRAM_FIFO_DATA153 (153UL)
#define CAM_HISTOGRAM_FIFO_DATA154 (154UL)
#define CAM_HISTOGRAM_FIFO_DATA155 (155UL)
#define CAM_HISTOGRAM_FIFO_DATA156 (156UL)
#define CAM_HISTOGRAM_FIFO_DATA157 (157UL)
#define CAM_HISTOGRAM_FIFO_DATA158 (158UL)
#define CAM_HISTOGRAM_FIFO_DATA159 (159UL)
#define CAM_HISTOGRAM_FIFO_DATA160 (160UL)
#define CAM_HISTOGRAM_FIFO_DATA161 (161UL)
#define CAM_HISTOGRAM_FIFO_DATA162 (162UL)
#define CAM_HISTOGRAM_FIFO_DATA163 (163UL)
#define CAM_HISTOGRAM_FIFO_DATA164 (164UL)
#define CAM_HISTOGRAM_FIFO_DATA165 (165UL)
#define CAM_HISTOGRAM_FIFO_DATA166 (166UL)
#define CAM_HISTOGRAM_FIFO_DATA167 (167UL)
#define CAM_HISTOGRAM_FIFO_DATA168 (168UL)
#define CAM_HISTOGRAM_FIFO_DATA169 (169UL)
#define CAM_HISTOGRAM_FIFO_DATA170 (170UL)
#define CAM_HISTOGRAM_FIFO_DATA171 (171UL)
#define CAM_HISTOGRAM_FIFO_DATA172 (172UL)
#define CAM_HISTOGRAM_FIFO_DATA173 (173UL)
#define CAM_HISTOGRAM_FIFO_DATA174 (174UL)
#define CAM_HISTOGRAM_FIFO_DATA175 (175UL)
#define CAM_HISTOGRAM_FIFO_DATA176 (176UL)
#define CAM_HISTOGRAM_FIFO_DATA177 (177UL)
#define CAM_HISTOGRAM_FIFO_DATA178 (178UL)
#define CAM_HISTOGRAM_FIFO_DATA179 (179UL)
#define CAM_HISTOGRAM_FIFO_DATA180 (180UL)
#define CAM_HISTOGRAM_FIFO_DATA181 (181UL)
#define CAM_HISTOGRAM_FIFO_DATA182 (182UL)
#define CAM_HISTOGRAM_FIFO_DATA183 (183UL)
#define CAM_HISTOGRAM_FIFO_DATA184 (184UL)
#define CAM_HISTOGRAM_FIFO_DATA185 (185UL)
#define CAM_HISTOGRAM_FIFO_DATA186 (186UL)
#define CAM_HISTOGRAM_FIFO_DATA187 (187UL)
#define CAM_HISTOGRAM_FIFO_DATA188 (188UL)
#define CAM_HISTOGRAM_FIFO_DATA189 (189UL)
#define CAM_HISTOGRAM_FIFO_DATA190 (190UL)
#define CAM_HISTOGRAM_FIFO_DATA191 (191UL)
#define CAM_HISTOGRAM_FIFO_DATA192 (192UL)
#define CAM_HISTOGRAM_FIFO_DATA193 (193UL)
#define CAM_HISTOGRAM_FIFO_DATA194 (194UL)
#define CAM_HISTOGRAM_FIFO_DATA195 (195UL)
#define CAM_HISTOGRAM_FIFO_DATA196 (196UL)
#define CAM_HISTOGRAM_FIFO_DATA197 (197UL)
#define CAM_HISTOGRAM_FIFO_DATA198 (198UL)
#define CAM_HISTOGRAM_FIFO_DATA199 (199UL)
#define CAM_HISTOGRAM_FIFO_DATA200 (200UL)
#define CAM_HISTOGRAM_FIFO_DATA201 (201UL)
#define CAM_HISTOGRAM_FIFO_DATA202 (202UL)
#define CAM_HISTOGRAM_FIFO_DATA203 (203UL)
#define CAM_HISTOGRAM_FIFO_DATA204 (204UL)
#define CAM_HISTOGRAM_FIFO_DATA205 (205UL)
#define CAM_HISTOGRAM_FIFO_DATA206 (206UL)
#define CAM_HISTOGRAM_FIFO_DATA207 (207UL)
#define CAM_HISTOGRAM_FIFO_DATA208 (208UL)
#define CAM_HISTOGRAM_FIFO_DATA209 (209UL)
#define CAM_HISTOGRAM_FIFO_DATA210 (210UL)
#define CAM_HISTOGRAM_FIFO_DATA211 (211UL)
#define CAM_HISTOGRAM_FIFO_DATA212 (212UL)
#define CAM_HISTOGRAM_FIFO_DATA213 (213UL)
#define CAM_HISTOGRAM_FIFO_DATA214 (214UL)
#define CAM_HISTOGRAM_FIFO_DATA215 (215UL)
#define CAM_HISTOGRAM_FIFO_DATA216 (216UL)
#define CAM_HISTOGRAM_FIFO_DATA217 (217UL)
#define CAM_HISTOGRAM_FIFO_DATA218 (218UL)
#define CAM_HISTOGRAM_FIFO_DATA219 (219UL)
#define CAM_HISTOGRAM_FIFO_DATA220 (220UL)
#define CAM_HISTOGRAM_FIFO_DATA221 (221UL)
#define CAM_HISTOGRAM_FIFO_DATA222 (222UL)
#define CAM_HISTOGRAM_FIFO_DATA223 (223UL)
#define CAM_HISTOGRAM_FIFO_DATA224 (224UL)
#define CAM_HISTOGRAM_FIFO_DATA225 (225UL)
#define CAM_HISTOGRAM_FIFO_DATA226 (226UL)
#define CAM_HISTOGRAM_FIFO_DATA227 (227UL)
#define CAM_HISTOGRAM_FIFO_DATA228 (228UL)
#define CAM_HISTOGRAM_FIFO_DATA229 (229UL)
#define CAM_HISTOGRAM_FIFO_DATA230 (230UL)
#define CAM_HISTOGRAM_FIFO_DATA231 (231UL)
#define CAM_HISTOGRAM_FIFO_DATA232 (232UL)
#define CAM_HISTOGRAM_FIFO_DATA233 (233UL)
#define CAM_HISTOGRAM_FIFO_DATA234 (234UL)
#define CAM_HISTOGRAM_FIFO_DATA235 (235UL)
#define CAM_HISTOGRAM_FIFO_DATA236 (236UL)
#define CAM_HISTOGRAM_FIFO_DATA237 (237UL)
#define CAM_HISTOGRAM_FIFO_DATA238 (238UL)
#define CAM_HISTOGRAM_FIFO_DATA239 (239UL)
#define CAM_HISTOGRAM_FIFO_DATA240 (240UL)
#define CAM_HISTOGRAM_FIFO_DATA241 (241UL)
#define CAM_HISTOGRAM_FIFO_DATA242 (242UL)
#define CAM_HISTOGRAM_FIFO_DATA243 (243UL)
#define CAM_HISTOGRAM_FIFO_DATA244 (244UL)
#define CAM_HISTOGRAM_FIFO_DATA245 (245UL)
#define CAM_HISTOGRAM_FIFO_DATA246 (246UL)
#define CAM_HISTOGRAM_FIFO_DATA247 (247UL)
#define CAM_HISTOGRAM_FIFO_DATA248 (248UL)
#define CAM_HISTOGRAM_FIFO_DATA249 (249UL)
#define CAM_HISTOGRAM_FIFO_DATA250 (250UL)
#define CAM_HISTOGRAM_FIFO_DATA251 (251UL)
#define CAM_HISTOGRAM_FIFO_DATA252 (252UL)
#define CAM_HISTOGRAM_FIFO_DATA253 (253UL)
#define CAM_HISTOGRAM_FIFO_DATA254 (254UL)
#define CAM_HISTOGRAM_FIFO_DATA255 (255UL)


#endif /* HPM_CAM_H */
