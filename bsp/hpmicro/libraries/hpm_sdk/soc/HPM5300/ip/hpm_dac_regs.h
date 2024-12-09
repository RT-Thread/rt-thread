/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DAC_H
#define HPM_DAC_H

typedef struct {
    __W  uint32_t CFG0;                        /* 0x0:  */
    __RW uint32_t CFG1;                        /* 0x4:  */
    __RW uint32_t CFG2;                        /* 0x8:  */
    __R  uint8_t  RESERVED0[4];                /* 0xC - 0xF: Reserved */
    __RW uint32_t STEP_CFG[4];                 /* 0x10 - 0x1C:  */
    __RW uint32_t BUF_ADDR[2];                 /* 0x20 - 0x24:  */
    __RW uint32_t BUF_LENGTH;                  /* 0x28:  */
    __R  uint8_t  RESERVED1[4];                /* 0x2C - 0x2F: Reserved */
    __W  uint32_t IRQ_STS;                     /* 0x30:  */
    __RW uint32_t IRQ_EN;                      /* 0x34:  */
    __RW uint32_t DMA_EN;                      /* 0x38:  */
    __R  uint8_t  RESERVED2[4];                /* 0x3C - 0x3F: Reserved */
    __RW uint32_t ANA_CFG0;                    /* 0x40:  */
    __RW uint32_t CFG0_BAK;                    /* 0x44:  */
    __RW uint32_t STATUS0;                     /* 0x48:  */
} DAC_Type;


/* Bitfield definition for register: CFG0 */
/*
 * SW_DAC_DATA (WO)
 *
 * dac data used in direct mode(dac_mode==2'b10)
 */
#define DAC_CFG0_SW_DAC_DATA_MASK (0xFFF0000UL)
#define DAC_CFG0_SW_DAC_DATA_SHIFT (16U)
#define DAC_CFG0_SW_DAC_DATA_SET(x) (((uint32_t)(x) << DAC_CFG0_SW_DAC_DATA_SHIFT) & DAC_CFG0_SW_DAC_DATA_MASK)
#define DAC_CFG0_SW_DAC_DATA_GET(x) (((uint32_t)(x) & DAC_CFG0_SW_DAC_DATA_MASK) >> DAC_CFG0_SW_DAC_DATA_SHIFT)

/*
 * DMA_AHB_EN (WO)
 *
 * set to enable internal DMA, it will read one burst if enough space in FIFO.
 * Should only be used in buffer mode.
 */
#define DAC_CFG0_DMA_AHB_EN_MASK (0x200U)
#define DAC_CFG0_DMA_AHB_EN_SHIFT (9U)
#define DAC_CFG0_DMA_AHB_EN_SET(x) (((uint32_t)(x) << DAC_CFG0_DMA_AHB_EN_SHIFT) & DAC_CFG0_DMA_AHB_EN_MASK)
#define DAC_CFG0_DMA_AHB_EN_GET(x) (((uint32_t)(x) & DAC_CFG0_DMA_AHB_EN_MASK) >> DAC_CFG0_DMA_AHB_EN_SHIFT)

/*
 * SYNC_MODE (WO)
 *
 * 1: sync dac clock and ahb clock.
 *   all HW trigger signals are pulse in sync mode, can get faster response;
 * 0: async dac clock and ahb_clock
 *   all HW trigger signals should be level and should be more than one dac clock cycle,  used to get accurate output frequency(which may not be divided from AHB clock)
 */
#define DAC_CFG0_SYNC_MODE_MASK (0x100U)
#define DAC_CFG0_SYNC_MODE_SHIFT (8U)
#define DAC_CFG0_SYNC_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_SYNC_MODE_SHIFT) & DAC_CFG0_SYNC_MODE_MASK)
#define DAC_CFG0_SYNC_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_SYNC_MODE_MASK) >> DAC_CFG0_SYNC_MODE_SHIFT)

/*
 * TRIG_MODE (WO)
 *
 * 0: single mode, one trigger pulse will send one 12bit data to DAC analog;
 * 1: continual mode, if trigger signal(either  or HW) is set, DAC will send data if FIFO is not empty, if trigger signal is clear, DAC will stop send data.
 */
#define DAC_CFG0_TRIG_MODE_MASK (0x80U)
#define DAC_CFG0_TRIG_MODE_SHIFT (7U)
#define DAC_CFG0_TRIG_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_TRIG_MODE_SHIFT) & DAC_CFG0_TRIG_MODE_MASK)
#define DAC_CFG0_TRIG_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_TRIG_MODE_MASK) >> DAC_CFG0_TRIG_MODE_SHIFT)

/*
 * HW_TRIG_EN (WO)
 *
 * set to use trigger signal from trigger_mux, user should config it to pulse in single mode, and level in continual mode
 */
#define DAC_CFG0_HW_TRIG_EN_MASK (0x40U)
#define DAC_CFG0_HW_TRIG_EN_SHIFT (6U)
#define DAC_CFG0_HW_TRIG_EN_SET(x) (((uint32_t)(x) << DAC_CFG0_HW_TRIG_EN_SHIFT) & DAC_CFG0_HW_TRIG_EN_MASK)
#define DAC_CFG0_HW_TRIG_EN_GET(x) (((uint32_t)(x) & DAC_CFG0_HW_TRIG_EN_MASK) >> DAC_CFG0_HW_TRIG_EN_SHIFT)

/*
 * DAC_MODE (WO)
 *
 * 00: direct mode, DAC output the fixed configured data(from sw_dac_data)
 * 01: step mode, DAC output from start_point to end point, with configured step, can step up or step down
 * 10: buffer mode,  read data from buffer, then output to analog, internal DMA will load next burst if enough space in local FIFO;
 * 11: trigger mode,  DAC output from external trigger signals
 * Note:
 * Trigger mode is not supported in hpm63xx and hpm62xx families.
 */
#define DAC_CFG0_DAC_MODE_MASK (0x30U)
#define DAC_CFG0_DAC_MODE_SHIFT (4U)
#define DAC_CFG0_DAC_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_DAC_MODE_SHIFT) & DAC_CFG0_DAC_MODE_MASK)
#define DAC_CFG0_DAC_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_DAC_MODE_MASK) >> DAC_CFG0_DAC_MODE_SHIFT)

/*
 * BUF_DATA_MODE (WO)
 *
 * data structure for buffer mode,
 * 0: each 32-bit data contains 2 points, b11:0 for first, b27:16 for second.
 * 1: each 32-bit data contains 1 point, b11:0 for first
 */
#define DAC_CFG0_BUF_DATA_MODE_MASK (0x8U)
#define DAC_CFG0_BUF_DATA_MODE_SHIFT (3U)
#define DAC_CFG0_BUF_DATA_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_BUF_DATA_MODE_SHIFT) & DAC_CFG0_BUF_DATA_MODE_MASK)
#define DAC_CFG0_BUF_DATA_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_BUF_DATA_MODE_MASK) >> DAC_CFG0_BUF_DATA_MODE_SHIFT)

/*
 * HBURST_CFG (WO)
 *
 * DAC support following fixed burst only
 * 000-SINGLE;  011-INCR4;  101: INCR8
 * others are reserved
 */
#define DAC_CFG0_HBURST_CFG_MASK (0x7U)
#define DAC_CFG0_HBURST_CFG_SHIFT (0U)
#define DAC_CFG0_HBURST_CFG_SET(x) (((uint32_t)(x) << DAC_CFG0_HBURST_CFG_SHIFT) & DAC_CFG0_HBURST_CFG_MASK)
#define DAC_CFG0_HBURST_CFG_GET(x) (((uint32_t)(x) & DAC_CFG0_HBURST_CFG_MASK) >> DAC_CFG0_HBURST_CFG_SHIFT)

/* Bitfield definition for register: CFG1 */
/*
 * ANA_CLK_EN (RW)
 *
 * set to enable analog clock(divided by ana_div_cfg)
 * need to be set in direct mode and trigger mode
 */
#define DAC_CFG1_ANA_CLK_EN_MASK (0x40000UL)
#define DAC_CFG1_ANA_CLK_EN_SHIFT (18U)
#define DAC_CFG1_ANA_CLK_EN_SET(x) (((uint32_t)(x) << DAC_CFG1_ANA_CLK_EN_SHIFT) & DAC_CFG1_ANA_CLK_EN_MASK)
#define DAC_CFG1_ANA_CLK_EN_GET(x) (((uint32_t)(x) & DAC_CFG1_ANA_CLK_EN_MASK) >> DAC_CFG1_ANA_CLK_EN_SHIFT)

/*
 * ANA_DIV_CFG (RW)
 *
 * clock divider config for ana_clk to dac analog;
 * 00:  div2
 * 01:  div4
 * 10:  div6
 * 11:  div8
 */
#define DAC_CFG1_ANA_DIV_CFG_MASK (0x30000UL)
#define DAC_CFG1_ANA_DIV_CFG_SHIFT (16U)
#define DAC_CFG1_ANA_DIV_CFG_SET(x) (((uint32_t)(x) << DAC_CFG1_ANA_DIV_CFG_SHIFT) & DAC_CFG1_ANA_DIV_CFG_MASK)
#define DAC_CFG1_ANA_DIV_CFG_GET(x) (((uint32_t)(x) & DAC_CFG1_ANA_DIV_CFG_MASK) >> DAC_CFG1_ANA_DIV_CFG_SHIFT)

/*
 * DIV_CFG (RW)
 *
 * step mode and buffer mode:
 *   defines how many clk_dac cycles to change data to analog, should configured to less than 1MHz data rate.
 * Direct mode and trigger mode:
 *   defines how many clk_dac cycles to accpet the input data, dac will not accept new written data or trigger data before the clock cycles passed. should configured to less than 1MHz.
 * Note:
 * For direct mode and trigger mode, this config is not supported in hpm63xx and hpm62xx families.
 */
#define DAC_CFG1_DIV_CFG_MASK (0xFFFFU)
#define DAC_CFG1_DIV_CFG_SHIFT (0U)
#define DAC_CFG1_DIV_CFG_SET(x) (((uint32_t)(x) << DAC_CFG1_DIV_CFG_SHIFT) & DAC_CFG1_DIV_CFG_MASK)
#define DAC_CFG1_DIV_CFG_GET(x) (((uint32_t)(x) & DAC_CFG1_DIV_CFG_MASK) >> DAC_CFG1_DIV_CFG_SHIFT)

/* Bitfield definition for register: CFG2 */
/*
 * DMA_RST1 (WO)
 *
 * set to reset dma read pointer to buf1_start_addr;
 * if set both dma_rst0&dma_rst1, will set to buf0_start_addr
 * user can set fifo_clr bit when use dma_rst*
 */
#define DAC_CFG2_DMA_RST1_MASK (0x80U)
#define DAC_CFG2_DMA_RST1_SHIFT (7U)
#define DAC_CFG2_DMA_RST1_SET(x) (((uint32_t)(x) << DAC_CFG2_DMA_RST1_SHIFT) & DAC_CFG2_DMA_RST1_MASK)
#define DAC_CFG2_DMA_RST1_GET(x) (((uint32_t)(x) & DAC_CFG2_DMA_RST1_MASK) >> DAC_CFG2_DMA_RST1_SHIFT)

/*
 * DMA_RST0 (WO)
 *
 * set to reset dma read pointer to buf0_start_addr
 */
#define DAC_CFG2_DMA_RST0_MASK (0x40U)
#define DAC_CFG2_DMA_RST0_SHIFT (6U)
#define DAC_CFG2_DMA_RST0_SET(x) (((uint32_t)(x) << DAC_CFG2_DMA_RST0_SHIFT) & DAC_CFG2_DMA_RST0_MASK)
#define DAC_CFG2_DMA_RST0_GET(x) (((uint32_t)(x) & DAC_CFG2_DMA_RST0_MASK) >> DAC_CFG2_DMA_RST0_SHIFT)

/*
 * FIFO_CLR (WO)
 *
 * set to clear FIFO content(set both read/write pointer to 0)
 */
#define DAC_CFG2_FIFO_CLR_MASK (0x20U)
#define DAC_CFG2_FIFO_CLR_SHIFT (5U)
#define DAC_CFG2_FIFO_CLR_SET(x) (((uint32_t)(x) << DAC_CFG2_FIFO_CLR_SHIFT) & DAC_CFG2_FIFO_CLR_MASK)
#define DAC_CFG2_FIFO_CLR_GET(x) (((uint32_t)(x) & DAC_CFG2_FIFO_CLR_MASK) >> DAC_CFG2_FIFO_CLR_SHIFT)

/*
 * BUF_SW_TRIG (RW)
 *
 * software trigger for buffer mode,
 * W1C in single mode.
 * RW in continual mode
 */
#define DAC_CFG2_BUF_SW_TRIG_MASK (0x10U)
#define DAC_CFG2_BUF_SW_TRIG_SHIFT (4U)
#define DAC_CFG2_BUF_SW_TRIG_SET(x) (((uint32_t)(x) << DAC_CFG2_BUF_SW_TRIG_SHIFT) & DAC_CFG2_BUF_SW_TRIG_MASK)
#define DAC_CFG2_BUF_SW_TRIG_GET(x) (((uint32_t)(x) & DAC_CFG2_BUF_SW_TRIG_MASK) >> DAC_CFG2_BUF_SW_TRIG_SHIFT)

/*
 * STEP_SW_TRIG3 (RW)
 *
 */
#define DAC_CFG2_STEP_SW_TRIG3_MASK (0x8U)
#define DAC_CFG2_STEP_SW_TRIG3_SHIFT (3U)
#define DAC_CFG2_STEP_SW_TRIG3_SET(x) (((uint32_t)(x) << DAC_CFG2_STEP_SW_TRIG3_SHIFT) & DAC_CFG2_STEP_SW_TRIG3_MASK)
#define DAC_CFG2_STEP_SW_TRIG3_GET(x) (((uint32_t)(x) & DAC_CFG2_STEP_SW_TRIG3_MASK) >> DAC_CFG2_STEP_SW_TRIG3_SHIFT)

/*
 * STEP_SW_TRIG2 (RW)
 *
 */
#define DAC_CFG2_STEP_SW_TRIG2_MASK (0x4U)
#define DAC_CFG2_STEP_SW_TRIG2_SHIFT (2U)
#define DAC_CFG2_STEP_SW_TRIG2_SET(x) (((uint32_t)(x) << DAC_CFG2_STEP_SW_TRIG2_SHIFT) & DAC_CFG2_STEP_SW_TRIG2_MASK)
#define DAC_CFG2_STEP_SW_TRIG2_GET(x) (((uint32_t)(x) & DAC_CFG2_STEP_SW_TRIG2_MASK) >> DAC_CFG2_STEP_SW_TRIG2_SHIFT)

/*
 * STEP_SW_TRIG1 (RW)
 *
 */
#define DAC_CFG2_STEP_SW_TRIG1_MASK (0x2U)
#define DAC_CFG2_STEP_SW_TRIG1_SHIFT (1U)
#define DAC_CFG2_STEP_SW_TRIG1_SET(x) (((uint32_t)(x) << DAC_CFG2_STEP_SW_TRIG1_SHIFT) & DAC_CFG2_STEP_SW_TRIG1_MASK)
#define DAC_CFG2_STEP_SW_TRIG1_GET(x) (((uint32_t)(x) & DAC_CFG2_STEP_SW_TRIG1_MASK) >> DAC_CFG2_STEP_SW_TRIG1_SHIFT)

/*
 * STEP_SW_TRIG0 (RW)
 *
 * software trigger0 for step mode,
 * W1C in single mode.
 * RW in continual mode
 */
#define DAC_CFG2_STEP_SW_TRIG0_MASK (0x1U)
#define DAC_CFG2_STEP_SW_TRIG0_SHIFT (0U)
#define DAC_CFG2_STEP_SW_TRIG0_SET(x) (((uint32_t)(x) << DAC_CFG2_STEP_SW_TRIG0_SHIFT) & DAC_CFG2_STEP_SW_TRIG0_MASK)
#define DAC_CFG2_STEP_SW_TRIG0_GET(x) (((uint32_t)(x) & DAC_CFG2_STEP_SW_TRIG0_MASK) >> DAC_CFG2_STEP_SW_TRIG0_SHIFT)

/* Bitfield definition for register array: STEP_CFG */
/*
 * ROUND_MODE (RW)
 *
 * 0: stop at end point;
 * 1: reload start point, step again
 */
#define DAC_STEP_CFG_ROUND_MODE_MASK (0x20000000UL)
#define DAC_STEP_CFG_ROUND_MODE_SHIFT (29U)
#define DAC_STEP_CFG_ROUND_MODE_SET(x) (((uint32_t)(x) << DAC_STEP_CFG_ROUND_MODE_SHIFT) & DAC_STEP_CFG_ROUND_MODE_MASK)
#define DAC_STEP_CFG_ROUND_MODE_GET(x) (((uint32_t)(x) & DAC_STEP_CFG_ROUND_MODE_MASK) >> DAC_STEP_CFG_ROUND_MODE_SHIFT)

/*
 * UP_DOWN (RW)
 *
 * 0 for up, 1 for down
 */
#define DAC_STEP_CFG_UP_DOWN_MASK (0x10000000UL)
#define DAC_STEP_CFG_UP_DOWN_SHIFT (28U)
#define DAC_STEP_CFG_UP_DOWN_SET(x) (((uint32_t)(x) << DAC_STEP_CFG_UP_DOWN_SHIFT) & DAC_STEP_CFG_UP_DOWN_MASK)
#define DAC_STEP_CFG_UP_DOWN_GET(x) (((uint32_t)(x) & DAC_STEP_CFG_UP_DOWN_MASK) >> DAC_STEP_CFG_UP_DOWN_SHIFT)

/*
 * END_POINT (RW)
 *
 */
#define DAC_STEP_CFG_END_POINT_MASK (0xFFF0000UL)
#define DAC_STEP_CFG_END_POINT_SHIFT (16U)
#define DAC_STEP_CFG_END_POINT_SET(x) (((uint32_t)(x) << DAC_STEP_CFG_END_POINT_SHIFT) & DAC_STEP_CFG_END_POINT_MASK)
#define DAC_STEP_CFG_END_POINT_GET(x) (((uint32_t)(x) & DAC_STEP_CFG_END_POINT_MASK) >> DAC_STEP_CFG_END_POINT_SHIFT)

/*
 * STEP_NUM (RW)
 *
 * output data change step_num each DAC clock cycle.
 * Ex: if step_num=3, output data sequence is 0,3,6,9
 * NOTE:  user should make sure end_point can be reached if step_num is not 1
 * if step_num is 0, output data will always at start point
 */
#define DAC_STEP_CFG_STEP_NUM_MASK (0xF000U)
#define DAC_STEP_CFG_STEP_NUM_SHIFT (12U)
#define DAC_STEP_CFG_STEP_NUM_SET(x) (((uint32_t)(x) << DAC_STEP_CFG_STEP_NUM_SHIFT) & DAC_STEP_CFG_STEP_NUM_MASK)
#define DAC_STEP_CFG_STEP_NUM_GET(x) (((uint32_t)(x) & DAC_STEP_CFG_STEP_NUM_MASK) >> DAC_STEP_CFG_STEP_NUM_SHIFT)

/*
 * START_POINT (RW)
 *
 */
#define DAC_STEP_CFG_START_POINT_MASK (0xFFFU)
#define DAC_STEP_CFG_START_POINT_SHIFT (0U)
#define DAC_STEP_CFG_START_POINT_SET(x) (((uint32_t)(x) << DAC_STEP_CFG_START_POINT_SHIFT) & DAC_STEP_CFG_START_POINT_MASK)
#define DAC_STEP_CFG_START_POINT_GET(x) (((uint32_t)(x) & DAC_STEP_CFG_START_POINT_MASK) >> DAC_STEP_CFG_START_POINT_SHIFT)

/* Bitfield definition for register array: BUF_ADDR */
/*
 * BUF_START_ADDR (RW)
 *
 * buffer start address, should be 4-byte aligned
 * AHB burst can't cross 1K-byte boundary, user should config the address/length/burst to avoid such issue.
 */
#define DAC_BUF_ADDR_BUF_START_ADDR_MASK (0xFFFFFFFCUL)
#define DAC_BUF_ADDR_BUF_START_ADDR_SHIFT (2U)
#define DAC_BUF_ADDR_BUF_START_ADDR_SET(x) (((uint32_t)(x) << DAC_BUF_ADDR_BUF_START_ADDR_SHIFT) & DAC_BUF_ADDR_BUF_START_ADDR_MASK)
#define DAC_BUF_ADDR_BUF_START_ADDR_GET(x) (((uint32_t)(x) & DAC_BUF_ADDR_BUF_START_ADDR_MASK) >> DAC_BUF_ADDR_BUF_START_ADDR_SHIFT)

/*
 * BUF_STOP (RW)
 *
 * set to stop read point at end of bufffer0
 */
#define DAC_BUF_ADDR_BUF_STOP_MASK (0x1U)
#define DAC_BUF_ADDR_BUF_STOP_SHIFT (0U)
#define DAC_BUF_ADDR_BUF_STOP_SET(x) (((uint32_t)(x) << DAC_BUF_ADDR_BUF_STOP_SHIFT) & DAC_BUF_ADDR_BUF_STOP_MASK)
#define DAC_BUF_ADDR_BUF_STOP_GET(x) (((uint32_t)(x) & DAC_BUF_ADDR_BUF_STOP_MASK) >> DAC_BUF_ADDR_BUF_STOP_SHIFT)

/* Bitfield definition for register: BUF_LENGTH */
/*
 * BUF1_LEN (RW)
 *
 * buffer length, 1 indicate one 32bit date, 256K-byte max for one buffer
 */
#define DAC_BUF_LENGTH_BUF1_LEN_MASK (0xFFFF0000UL)
#define DAC_BUF_LENGTH_BUF1_LEN_SHIFT (16U)
#define DAC_BUF_LENGTH_BUF1_LEN_SET(x) (((uint32_t)(x) << DAC_BUF_LENGTH_BUF1_LEN_SHIFT) & DAC_BUF_LENGTH_BUF1_LEN_MASK)
#define DAC_BUF_LENGTH_BUF1_LEN_GET(x) (((uint32_t)(x) & DAC_BUF_LENGTH_BUF1_LEN_MASK) >> DAC_BUF_LENGTH_BUF1_LEN_SHIFT)

/*
 * BUF0_LEN (RW)
 *
 */
#define DAC_BUF_LENGTH_BUF0_LEN_MASK (0xFFFFU)
#define DAC_BUF_LENGTH_BUF0_LEN_SHIFT (0U)
#define DAC_BUF_LENGTH_BUF0_LEN_SET(x) (((uint32_t)(x) << DAC_BUF_LENGTH_BUF0_LEN_SHIFT) & DAC_BUF_LENGTH_BUF0_LEN_MASK)
#define DAC_BUF_LENGTH_BUF0_LEN_GET(x) (((uint32_t)(x) & DAC_BUF_LENGTH_BUF0_LEN_MASK) >> DAC_BUF_LENGTH_BUF0_LEN_SHIFT)

/* Bitfield definition for register: IRQ_STS */
/*
 * STEP_CMPT (W1C)
 *
 */
#define DAC_IRQ_STS_STEP_CMPT_MASK (0x10U)
#define DAC_IRQ_STS_STEP_CMPT_SHIFT (4U)
#define DAC_IRQ_STS_STEP_CMPT_SET(x) (((uint32_t)(x) << DAC_IRQ_STS_STEP_CMPT_SHIFT) & DAC_IRQ_STS_STEP_CMPT_MASK)
#define DAC_IRQ_STS_STEP_CMPT_GET(x) (((uint32_t)(x) & DAC_IRQ_STS_STEP_CMPT_MASK) >> DAC_IRQ_STS_STEP_CMPT_SHIFT)

/*
 * AHB_ERROR (W1C)
 *
 * set if hresp==2'b01(ERROR)
 */
#define DAC_IRQ_STS_AHB_ERROR_MASK (0x8U)
#define DAC_IRQ_STS_AHB_ERROR_SHIFT (3U)
#define DAC_IRQ_STS_AHB_ERROR_SET(x) (((uint32_t)(x) << DAC_IRQ_STS_AHB_ERROR_SHIFT) & DAC_IRQ_STS_AHB_ERROR_MASK)
#define DAC_IRQ_STS_AHB_ERROR_GET(x) (((uint32_t)(x) & DAC_IRQ_STS_AHB_ERROR_MASK) >> DAC_IRQ_STS_AHB_ERROR_SHIFT)

/*
 * FIFO_EMPTY (W1C)
 *
 */
#define DAC_IRQ_STS_FIFO_EMPTY_MASK (0x4U)
#define DAC_IRQ_STS_FIFO_EMPTY_SHIFT (2U)
#define DAC_IRQ_STS_FIFO_EMPTY_SET(x) (((uint32_t)(x) << DAC_IRQ_STS_FIFO_EMPTY_SHIFT) & DAC_IRQ_STS_FIFO_EMPTY_MASK)
#define DAC_IRQ_STS_FIFO_EMPTY_GET(x) (((uint32_t)(x) & DAC_IRQ_STS_FIFO_EMPTY_MASK) >> DAC_IRQ_STS_FIFO_EMPTY_SHIFT)

/*
 * BUF1_CMPT (W1C)
 *
 */
#define DAC_IRQ_STS_BUF1_CMPT_MASK (0x2U)
#define DAC_IRQ_STS_BUF1_CMPT_SHIFT (1U)
#define DAC_IRQ_STS_BUF1_CMPT_SET(x) (((uint32_t)(x) << DAC_IRQ_STS_BUF1_CMPT_SHIFT) & DAC_IRQ_STS_BUF1_CMPT_MASK)
#define DAC_IRQ_STS_BUF1_CMPT_GET(x) (((uint32_t)(x) & DAC_IRQ_STS_BUF1_CMPT_MASK) >> DAC_IRQ_STS_BUF1_CMPT_SHIFT)

/*
 * BUF0_CMPT (W1C)
 *
 */
#define DAC_IRQ_STS_BUF0_CMPT_MASK (0x1U)
#define DAC_IRQ_STS_BUF0_CMPT_SHIFT (0U)
#define DAC_IRQ_STS_BUF0_CMPT_SET(x) (((uint32_t)(x) << DAC_IRQ_STS_BUF0_CMPT_SHIFT) & DAC_IRQ_STS_BUF0_CMPT_MASK)
#define DAC_IRQ_STS_BUF0_CMPT_GET(x) (((uint32_t)(x) & DAC_IRQ_STS_BUF0_CMPT_MASK) >> DAC_IRQ_STS_BUF0_CMPT_SHIFT)

/* Bitfield definition for register: IRQ_EN */
/*
 * STEP_CMPT (RW)
 *
 */
#define DAC_IRQ_EN_STEP_CMPT_MASK (0x10U)
#define DAC_IRQ_EN_STEP_CMPT_SHIFT (4U)
#define DAC_IRQ_EN_STEP_CMPT_SET(x) (((uint32_t)(x) << DAC_IRQ_EN_STEP_CMPT_SHIFT) & DAC_IRQ_EN_STEP_CMPT_MASK)
#define DAC_IRQ_EN_STEP_CMPT_GET(x) (((uint32_t)(x) & DAC_IRQ_EN_STEP_CMPT_MASK) >> DAC_IRQ_EN_STEP_CMPT_SHIFT)

/*
 * AHB_ERROR (RW)
 *
 */
#define DAC_IRQ_EN_AHB_ERROR_MASK (0x8U)
#define DAC_IRQ_EN_AHB_ERROR_SHIFT (3U)
#define DAC_IRQ_EN_AHB_ERROR_SET(x) (((uint32_t)(x) << DAC_IRQ_EN_AHB_ERROR_SHIFT) & DAC_IRQ_EN_AHB_ERROR_MASK)
#define DAC_IRQ_EN_AHB_ERROR_GET(x) (((uint32_t)(x) & DAC_IRQ_EN_AHB_ERROR_MASK) >> DAC_IRQ_EN_AHB_ERROR_SHIFT)

/*
 * FIFO_EMPTY (RW)
 *
 */
#define DAC_IRQ_EN_FIFO_EMPTY_MASK (0x4U)
#define DAC_IRQ_EN_FIFO_EMPTY_SHIFT (2U)
#define DAC_IRQ_EN_FIFO_EMPTY_SET(x) (((uint32_t)(x) << DAC_IRQ_EN_FIFO_EMPTY_SHIFT) & DAC_IRQ_EN_FIFO_EMPTY_MASK)
#define DAC_IRQ_EN_FIFO_EMPTY_GET(x) (((uint32_t)(x) & DAC_IRQ_EN_FIFO_EMPTY_MASK) >> DAC_IRQ_EN_FIFO_EMPTY_SHIFT)

/*
 * BUF1_CMPT (RW)
 *
 */
#define DAC_IRQ_EN_BUF1_CMPT_MASK (0x2U)
#define DAC_IRQ_EN_BUF1_CMPT_SHIFT (1U)
#define DAC_IRQ_EN_BUF1_CMPT_SET(x) (((uint32_t)(x) << DAC_IRQ_EN_BUF1_CMPT_SHIFT) & DAC_IRQ_EN_BUF1_CMPT_MASK)
#define DAC_IRQ_EN_BUF1_CMPT_GET(x) (((uint32_t)(x) & DAC_IRQ_EN_BUF1_CMPT_MASK) >> DAC_IRQ_EN_BUF1_CMPT_SHIFT)

/*
 * BUF0_CMPT (RW)
 *
 */
#define DAC_IRQ_EN_BUF0_CMPT_MASK (0x1U)
#define DAC_IRQ_EN_BUF0_CMPT_SHIFT (0U)
#define DAC_IRQ_EN_BUF0_CMPT_SET(x) (((uint32_t)(x) << DAC_IRQ_EN_BUF0_CMPT_SHIFT) & DAC_IRQ_EN_BUF0_CMPT_MASK)
#define DAC_IRQ_EN_BUF0_CMPT_GET(x) (((uint32_t)(x) & DAC_IRQ_EN_BUF0_CMPT_MASK) >> DAC_IRQ_EN_BUF0_CMPT_SHIFT)

/* Bitfield definition for register: DMA_EN */
/*
 * STEP_CMPT (RW)
 *
 */
#define DAC_DMA_EN_STEP_CMPT_MASK (0x10U)
#define DAC_DMA_EN_STEP_CMPT_SHIFT (4U)
#define DAC_DMA_EN_STEP_CMPT_SET(x) (((uint32_t)(x) << DAC_DMA_EN_STEP_CMPT_SHIFT) & DAC_DMA_EN_STEP_CMPT_MASK)
#define DAC_DMA_EN_STEP_CMPT_GET(x) (((uint32_t)(x) & DAC_DMA_EN_STEP_CMPT_MASK) >> DAC_DMA_EN_STEP_CMPT_SHIFT)

/*
 * BUF1_CMPT (RW)
 *
 */
#define DAC_DMA_EN_BUF1_CMPT_MASK (0x2U)
#define DAC_DMA_EN_BUF1_CMPT_SHIFT (1U)
#define DAC_DMA_EN_BUF1_CMPT_SET(x) (((uint32_t)(x) << DAC_DMA_EN_BUF1_CMPT_SHIFT) & DAC_DMA_EN_BUF1_CMPT_MASK)
#define DAC_DMA_EN_BUF1_CMPT_GET(x) (((uint32_t)(x) & DAC_DMA_EN_BUF1_CMPT_MASK) >> DAC_DMA_EN_BUF1_CMPT_SHIFT)

/*
 * BUF0_CMPT (RW)
 *
 */
#define DAC_DMA_EN_BUF0_CMPT_MASK (0x1U)
#define DAC_DMA_EN_BUF0_CMPT_SHIFT (0U)
#define DAC_DMA_EN_BUF0_CMPT_SET(x) (((uint32_t)(x) << DAC_DMA_EN_BUF0_CMPT_SHIFT) & DAC_DMA_EN_BUF0_CMPT_MASK)
#define DAC_DMA_EN_BUF0_CMPT_GET(x) (((uint32_t)(x) & DAC_DMA_EN_BUF0_CMPT_MASK) >> DAC_DMA_EN_BUF0_CMPT_SHIFT)

/* Bitfield definition for register: ANA_CFG0 */
/*
 * DAC12BIT_LP_MODE (RW)
 *
 */
#define DAC_ANA_CFG0_DAC12BIT_LP_MODE_MASK (0x100U)
#define DAC_ANA_CFG0_DAC12BIT_LP_MODE_SHIFT (8U)
#define DAC_ANA_CFG0_DAC12BIT_LP_MODE_SET(x) (((uint32_t)(x) << DAC_ANA_CFG0_DAC12BIT_LP_MODE_SHIFT) & DAC_ANA_CFG0_DAC12BIT_LP_MODE_MASK)
#define DAC_ANA_CFG0_DAC12BIT_LP_MODE_GET(x) (((uint32_t)(x) & DAC_ANA_CFG0_DAC12BIT_LP_MODE_MASK) >> DAC_ANA_CFG0_DAC12BIT_LP_MODE_SHIFT)

/*
 * DAC_CONFIG (RW)
 *
 */
#define DAC_ANA_CFG0_DAC_CONFIG_MASK (0xF0U)
#define DAC_ANA_CFG0_DAC_CONFIG_SHIFT (4U)
#define DAC_ANA_CFG0_DAC_CONFIG_SET(x) (((uint32_t)(x) << DAC_ANA_CFG0_DAC_CONFIG_SHIFT) & DAC_ANA_CFG0_DAC_CONFIG_MASK)
#define DAC_ANA_CFG0_DAC_CONFIG_GET(x) (((uint32_t)(x) & DAC_ANA_CFG0_DAC_CONFIG_MASK) >> DAC_ANA_CFG0_DAC_CONFIG_SHIFT)

/*
 * CALI_DELTA_V_CFG (RW)
 *
 */
#define DAC_ANA_CFG0_CALI_DELTA_V_CFG_MASK (0xCU)
#define DAC_ANA_CFG0_CALI_DELTA_V_CFG_SHIFT (2U)
#define DAC_ANA_CFG0_CALI_DELTA_V_CFG_SET(x) (((uint32_t)(x) << DAC_ANA_CFG0_CALI_DELTA_V_CFG_SHIFT) & DAC_ANA_CFG0_CALI_DELTA_V_CFG_MASK)
#define DAC_ANA_CFG0_CALI_DELTA_V_CFG_GET(x) (((uint32_t)(x) & DAC_ANA_CFG0_CALI_DELTA_V_CFG_MASK) >> DAC_ANA_CFG0_CALI_DELTA_V_CFG_SHIFT)

/*
 * BYPASS_CALI_GM (RW)
 *
 */
#define DAC_ANA_CFG0_BYPASS_CALI_GM_MASK (0x2U)
#define DAC_ANA_CFG0_BYPASS_CALI_GM_SHIFT (1U)
#define DAC_ANA_CFG0_BYPASS_CALI_GM_SET(x) (((uint32_t)(x) << DAC_ANA_CFG0_BYPASS_CALI_GM_SHIFT) & DAC_ANA_CFG0_BYPASS_CALI_GM_MASK)
#define DAC_ANA_CFG0_BYPASS_CALI_GM_GET(x) (((uint32_t)(x) & DAC_ANA_CFG0_BYPASS_CALI_GM_MASK) >> DAC_ANA_CFG0_BYPASS_CALI_GM_SHIFT)

/*
 * DAC12BIT_EN (RW)
 *
 */
#define DAC_ANA_CFG0_DAC12BIT_EN_MASK (0x1U)
#define DAC_ANA_CFG0_DAC12BIT_EN_SHIFT (0U)
#define DAC_ANA_CFG0_DAC12BIT_EN_SET(x) (((uint32_t)(x) << DAC_ANA_CFG0_DAC12BIT_EN_SHIFT) & DAC_ANA_CFG0_DAC12BIT_EN_MASK)
#define DAC_ANA_CFG0_DAC12BIT_EN_GET(x) (((uint32_t)(x) & DAC_ANA_CFG0_DAC12BIT_EN_MASK) >> DAC_ANA_CFG0_DAC12BIT_EN_SHIFT)

/* Bitfield definition for register: CFG0_BAK */
/*
 * SW_DAC_DATA (RW)
 *
 * dac data used in direct mode(dac_mode==2'b10)
 */
#define DAC_CFG0_BAK_SW_DAC_DATA_MASK (0xFFF0000UL)
#define DAC_CFG0_BAK_SW_DAC_DATA_SHIFT (16U)
#define DAC_CFG0_BAK_SW_DAC_DATA_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_SW_DAC_DATA_SHIFT) & DAC_CFG0_BAK_SW_DAC_DATA_MASK)
#define DAC_CFG0_BAK_SW_DAC_DATA_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_SW_DAC_DATA_MASK) >> DAC_CFG0_BAK_SW_DAC_DATA_SHIFT)

/*
 * DMA_AHB_EN (RW)
 *
 * set to enable internal DMA, it will read one burst if enough space in FIFO.
 * Should only be used in buffer mode.
 */
#define DAC_CFG0_BAK_DMA_AHB_EN_MASK (0x200U)
#define DAC_CFG0_BAK_DMA_AHB_EN_SHIFT (9U)
#define DAC_CFG0_BAK_DMA_AHB_EN_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_DMA_AHB_EN_SHIFT) & DAC_CFG0_BAK_DMA_AHB_EN_MASK)
#define DAC_CFG0_BAK_DMA_AHB_EN_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_DMA_AHB_EN_MASK) >> DAC_CFG0_BAK_DMA_AHB_EN_SHIFT)

/*
 * SYNC_MODE (RW)
 *
 * 1: sync dac clock and ahb clock.
 *   all HW trigger signals are pulse in sync mode, can get faster response;
 * 0: async dac clock and ahb_clock
 *   all HW trigger signals should be level and should be more than one dac clock cycle,  used to get accurate output frequency(which may not be divided from AHB clock)
 */
#define DAC_CFG0_BAK_SYNC_MODE_MASK (0x100U)
#define DAC_CFG0_BAK_SYNC_MODE_SHIFT (8U)
#define DAC_CFG0_BAK_SYNC_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_SYNC_MODE_SHIFT) & DAC_CFG0_BAK_SYNC_MODE_MASK)
#define DAC_CFG0_BAK_SYNC_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_SYNC_MODE_MASK) >> DAC_CFG0_BAK_SYNC_MODE_SHIFT)

/*
 * TRIG_MODE (RW)
 *
 * 0: single mode, one trigger pulse will send one 12bit data to DAC analog;
 * 1: continual mode, if trigger signal(either  or HW) is set, DAC will send data if FIFO is not empty, if trigger signal is clear, DAC will stop send data.
 */
#define DAC_CFG0_BAK_TRIG_MODE_MASK (0x80U)
#define DAC_CFG0_BAK_TRIG_MODE_SHIFT (7U)
#define DAC_CFG0_BAK_TRIG_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_TRIG_MODE_SHIFT) & DAC_CFG0_BAK_TRIG_MODE_MASK)
#define DAC_CFG0_BAK_TRIG_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_TRIG_MODE_MASK) >> DAC_CFG0_BAK_TRIG_MODE_SHIFT)

/*
 * HW_TRIG_EN (RW)
 *
 * set to use trigger signal from trigger_mux, user should config it to pulse in single mode, and level in continual mode
 */
#define DAC_CFG0_BAK_HW_TRIG_EN_MASK (0x40U)
#define DAC_CFG0_BAK_HW_TRIG_EN_SHIFT (6U)
#define DAC_CFG0_BAK_HW_TRIG_EN_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_HW_TRIG_EN_SHIFT) & DAC_CFG0_BAK_HW_TRIG_EN_MASK)
#define DAC_CFG0_BAK_HW_TRIG_EN_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_HW_TRIG_EN_MASK) >> DAC_CFG0_BAK_HW_TRIG_EN_SHIFT)

/*
 * DAC_MODE (RW)
 *
 * 00: direct mode, DAC output the fixed configured data(from sw_dac_data)
 * 01: step mode, DAC output from start_point to end point, with configured step, can step up or step down
 * 10: buffer mode,  read data from buffer, then output to analog, internal DMA will load next burst if enough space in local FIFO;
 */
#define DAC_CFG0_BAK_DAC_MODE_MASK (0x30U)
#define DAC_CFG0_BAK_DAC_MODE_SHIFT (4U)
#define DAC_CFG0_BAK_DAC_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_DAC_MODE_SHIFT) & DAC_CFG0_BAK_DAC_MODE_MASK)
#define DAC_CFG0_BAK_DAC_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_DAC_MODE_MASK) >> DAC_CFG0_BAK_DAC_MODE_SHIFT)

/*
 * BUF_DATA_MODE (RW)
 *
 * data structure for buffer mode,
 * 0: each 32-bit data contains 2 points, b11:0 for first, b27:16 for second.
 * 1: each 32-bit data contains 1 point, b11:0 for first
 */
#define DAC_CFG0_BAK_BUF_DATA_MODE_MASK (0x8U)
#define DAC_CFG0_BAK_BUF_DATA_MODE_SHIFT (3U)
#define DAC_CFG0_BAK_BUF_DATA_MODE_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_BUF_DATA_MODE_SHIFT) & DAC_CFG0_BAK_BUF_DATA_MODE_MASK)
#define DAC_CFG0_BAK_BUF_DATA_MODE_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_BUF_DATA_MODE_MASK) >> DAC_CFG0_BAK_BUF_DATA_MODE_SHIFT)

/*
 * HBURST_CFG (RW)
 *
 * DAC support following fixed burst only
 * 000-SINGLE;  011-INCR4;  101: INCR8
 * others are reserved
 */
#define DAC_CFG0_BAK_HBURST_CFG_MASK (0x7U)
#define DAC_CFG0_BAK_HBURST_CFG_SHIFT (0U)
#define DAC_CFG0_BAK_HBURST_CFG_SET(x) (((uint32_t)(x) << DAC_CFG0_BAK_HBURST_CFG_SHIFT) & DAC_CFG0_BAK_HBURST_CFG_MASK)
#define DAC_CFG0_BAK_HBURST_CFG_GET(x) (((uint32_t)(x) & DAC_CFG0_BAK_HBURST_CFG_MASK) >> DAC_CFG0_BAK_HBURST_CFG_SHIFT)

/* Bitfield definition for register: STATUS0 */
/*
 * CUR_BUF_OFFSET (RW)
 *
 */
#define DAC_STATUS0_CUR_BUF_OFFSET_MASK (0xFFFF00UL)
#define DAC_STATUS0_CUR_BUF_OFFSET_SHIFT (8U)
#define DAC_STATUS0_CUR_BUF_OFFSET_SET(x) (((uint32_t)(x) << DAC_STATUS0_CUR_BUF_OFFSET_SHIFT) & DAC_STATUS0_CUR_BUF_OFFSET_MASK)
#define DAC_STATUS0_CUR_BUF_OFFSET_GET(x) (((uint32_t)(x) & DAC_STATUS0_CUR_BUF_OFFSET_MASK) >> DAC_STATUS0_CUR_BUF_OFFSET_SHIFT)

/*
 * CUR_BUF_INDEX (RW)
 *
 */
#define DAC_STATUS0_CUR_BUF_INDEX_MASK (0x80U)
#define DAC_STATUS0_CUR_BUF_INDEX_SHIFT (7U)
#define DAC_STATUS0_CUR_BUF_INDEX_SET(x) (((uint32_t)(x) << DAC_STATUS0_CUR_BUF_INDEX_SHIFT) & DAC_STATUS0_CUR_BUF_INDEX_MASK)
#define DAC_STATUS0_CUR_BUF_INDEX_GET(x) (((uint32_t)(x) & DAC_STATUS0_CUR_BUF_INDEX_MASK) >> DAC_STATUS0_CUR_BUF_INDEX_SHIFT)



/* STEP_CFG register group index macro definition */
#define DAC_STEP_CFG_STEP0 (0UL)
#define DAC_STEP_CFG_STEP1 (1UL)
#define DAC_STEP_CFG_STEP2 (2UL)
#define DAC_STEP_CFG_STEP3 (3UL)

/* BUF_ADDR register group index macro definition */
#define DAC_BUF_ADDR_BUF0 (0UL)
#define DAC_BUF_ADDR_BUF1 (1UL)


#endif /* HPM_DAC_H */
