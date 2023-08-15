/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_ADC12_H
#define HPM_ADC12_H

typedef struct {
    __RW uint32_t CONFIG[12];                  /* 0x0 - 0x2C:  */
    __RW uint32_t TRG_DMA_ADDR;                /* 0x30:  */
    __RW uint32_t TRG_SW_STA;                  /* 0x34:  */
    __R  uint8_t  RESERVED0[968];              /* 0x38 - 0x3FF: Reserved */
    __R  uint32_t BUS_RESULT[19];              /* 0x400 - 0x448:  */
    __R  uint8_t  RESERVED1[180];              /* 0x44C - 0x4FF: Reserved */
    __RW uint32_t BUF_CFG0;                    /* 0x500:  */
    __R  uint8_t  RESERVED2[764];              /* 0x504 - 0x7FF: Reserved */
    __RW uint32_t SEQ_CFG0;                    /* 0x800:  */
    __RW uint32_t SEQ_DMA_ADDR;                /* 0x804:  */
    __R  uint32_t SEQ_WR_ADDR;                 /* 0x808:  */
    __RW uint32_t SEQ_DMA_CFG;                 /* 0x80C:  */
    __RW uint32_t SEQ_QUE[16];                 /* 0x810 - 0x84C:  */
    __R  uint8_t  RESERVED3[944];              /* 0x850 - 0xBFF: Reserved */
    struct {
        __RW uint32_t PRD_CFG;                 /* 0xC00:  */
        __RW uint32_t PRD_THSHD_CFG;           /* 0xC04:  */
        __R  uint32_t PRD_RESULT;              /* 0xC08:  */
        __R  uint8_t  RESERVED0[4];            /* 0xC0C - 0xC0F: Reserved */
    } PRD_CFG[19];
    __R  uint8_t  RESERVED4[720];              /* 0xD30 - 0xFFF: Reserved */
    __RW uint32_t SAMPLE_CFG[19];              /* 0x1000 - 0x1048:  */
    __R  uint8_t  RESERVED5[184];              /* 0x104C - 0x1103: Reserved */
    __RW uint32_t CONV_CFG1;                   /* 0x1104:  */
    __RW uint32_t ADC_CFG0;                    /* 0x1108:  */
    __R  uint8_t  RESERVED6[4];                /* 0x110C - 0x110F: Reserved */
    __RW uint32_t INT_STS;                     /* 0x1110:  */
    __RW uint32_t INT_EN;                      /* 0x1114:  */
    __R  uint8_t  RESERVED7[232];              /* 0x1118 - 0x11FF: Reserved */
    __RW uint32_t ANA_CTRL0;                   /* 0x1200:  */
    __RW uint32_t ANA_CTRL1;                   /* 0x1204:  */
    __R  uint8_t  RESERVED8[8];                /* 0x1208 - 0x120F: Reserved */
    __RW uint32_t ANA_STATUS;                  /* 0x1210:  */
} ADC12_Type;


/* Bitfield definition for register array: CONFIG */
/*
 * TRIG_LEN (WO)
 *
 * length for current trigger, can up to 4 conversions for one trigger, from 0 to 3
 */
#define ADC12_CONFIG_TRIG_LEN_MASK (0xC0000000UL)
#define ADC12_CONFIG_TRIG_LEN_SHIFT (30U)
#define ADC12_CONFIG_TRIG_LEN_SET(x) (((uint32_t)(x) << ADC12_CONFIG_TRIG_LEN_SHIFT) & ADC12_CONFIG_TRIG_LEN_MASK)
#define ADC12_CONFIG_TRIG_LEN_GET(x) (((uint32_t)(x) & ADC12_CONFIG_TRIG_LEN_MASK) >> ADC12_CONFIG_TRIG_LEN_SHIFT)

/*
 * INTEN3 (RW)
 *
 * interupt enable for 4th conversion
 */
#define ADC12_CONFIG_INTEN3_MASK (0x20000000UL)
#define ADC12_CONFIG_INTEN3_SHIFT (29U)
#define ADC12_CONFIG_INTEN3_SET(x) (((uint32_t)(x) << ADC12_CONFIG_INTEN3_SHIFT) & ADC12_CONFIG_INTEN3_MASK)
#define ADC12_CONFIG_INTEN3_GET(x) (((uint32_t)(x) & ADC12_CONFIG_INTEN3_MASK) >> ADC12_CONFIG_INTEN3_SHIFT)

/*
 * CHAN3 (RW)
 *
 * channel number for 4th conversion
 */
#define ADC12_CONFIG_CHAN3_MASK (0x1F000000UL)
#define ADC12_CONFIG_CHAN3_SHIFT (24U)
#define ADC12_CONFIG_CHAN3_SET(x) (((uint32_t)(x) << ADC12_CONFIG_CHAN3_SHIFT) & ADC12_CONFIG_CHAN3_MASK)
#define ADC12_CONFIG_CHAN3_GET(x) (((uint32_t)(x) & ADC12_CONFIG_CHAN3_MASK) >> ADC12_CONFIG_CHAN3_SHIFT)

/*
 * INTEN2 (RW)
 *
 * interupt enable for 3rd conversion
 */
#define ADC12_CONFIG_INTEN2_MASK (0x200000UL)
#define ADC12_CONFIG_INTEN2_SHIFT (21U)
#define ADC12_CONFIG_INTEN2_SET(x) (((uint32_t)(x) << ADC12_CONFIG_INTEN2_SHIFT) & ADC12_CONFIG_INTEN2_MASK)
#define ADC12_CONFIG_INTEN2_GET(x) (((uint32_t)(x) & ADC12_CONFIG_INTEN2_MASK) >> ADC12_CONFIG_INTEN2_SHIFT)

/*
 * CHAN2 (RW)
 *
 * channel number for 3rd conversion
 */
#define ADC12_CONFIG_CHAN2_MASK (0x1F0000UL)
#define ADC12_CONFIG_CHAN2_SHIFT (16U)
#define ADC12_CONFIG_CHAN2_SET(x) (((uint32_t)(x) << ADC12_CONFIG_CHAN2_SHIFT) & ADC12_CONFIG_CHAN2_MASK)
#define ADC12_CONFIG_CHAN2_GET(x) (((uint32_t)(x) & ADC12_CONFIG_CHAN2_MASK) >> ADC12_CONFIG_CHAN2_SHIFT)

/*
 * INTEN1 (RW)
 *
 * interupt enable for 2nd conversion
 */
#define ADC12_CONFIG_INTEN1_MASK (0x2000U)
#define ADC12_CONFIG_INTEN1_SHIFT (13U)
#define ADC12_CONFIG_INTEN1_SET(x) (((uint32_t)(x) << ADC12_CONFIG_INTEN1_SHIFT) & ADC12_CONFIG_INTEN1_MASK)
#define ADC12_CONFIG_INTEN1_GET(x) (((uint32_t)(x) & ADC12_CONFIG_INTEN1_MASK) >> ADC12_CONFIG_INTEN1_SHIFT)

/*
 * CHAN1 (RW)
 *
 * channel number for 2nd conversion
 */
#define ADC12_CONFIG_CHAN1_MASK (0x1F00U)
#define ADC12_CONFIG_CHAN1_SHIFT (8U)
#define ADC12_CONFIG_CHAN1_SET(x) (((uint32_t)(x) << ADC12_CONFIG_CHAN1_SHIFT) & ADC12_CONFIG_CHAN1_MASK)
#define ADC12_CONFIG_CHAN1_GET(x) (((uint32_t)(x) & ADC12_CONFIG_CHAN1_MASK) >> ADC12_CONFIG_CHAN1_SHIFT)

/*
 * INTEN0 (RW)
 *
 * interupt enable for 1st conversion
 */
#define ADC12_CONFIG_INTEN0_MASK (0x20U)
#define ADC12_CONFIG_INTEN0_SHIFT (5U)
#define ADC12_CONFIG_INTEN0_SET(x) (((uint32_t)(x) << ADC12_CONFIG_INTEN0_SHIFT) & ADC12_CONFIG_INTEN0_MASK)
#define ADC12_CONFIG_INTEN0_GET(x) (((uint32_t)(x) & ADC12_CONFIG_INTEN0_MASK) >> ADC12_CONFIG_INTEN0_SHIFT)

/*
 * CHAN0 (RW)
 *
 * channel number for 1st conversion
 */
#define ADC12_CONFIG_CHAN0_MASK (0x1FU)
#define ADC12_CONFIG_CHAN0_SHIFT (0U)
#define ADC12_CONFIG_CHAN0_SET(x) (((uint32_t)(x) << ADC12_CONFIG_CHAN0_SHIFT) & ADC12_CONFIG_CHAN0_MASK)
#define ADC12_CONFIG_CHAN0_GET(x) (((uint32_t)(x) & ADC12_CONFIG_CHAN0_MASK) >> ADC12_CONFIG_CHAN0_SHIFT)

/* Bitfield definition for register: TRG_DMA_ADDR */
/*
 * TRG_DMA_ADDR (RW)
 *
 * buffer start address for trigger queue, 192byte total, 16 bytes for each trigger (4 bytes for each conversion)
 */
#define ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK (0xFFFFFFFCUL)
#define ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_SHIFT (2U)
#define ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_SET(x) (((uint32_t)(x) << ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_SHIFT) & ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK)
#define ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_GET(x) (((uint32_t)(x) & ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK) >> ADC12_TRG_DMA_ADDR_TRG_DMA_ADDR_SHIFT)

/* Bitfield definition for register: TRG_SW_STA */
/*
 * TRG_SW_STA (RW)
 *
 * SW trigger start bit, HW will clear it after all conversions(up to 4) finished. SW should make sure it's 0 before set it.
 */
#define ADC12_TRG_SW_STA_TRG_SW_STA_MASK (0x10U)
#define ADC12_TRG_SW_STA_TRG_SW_STA_SHIFT (4U)
#define ADC12_TRG_SW_STA_TRG_SW_STA_SET(x) (((uint32_t)(x) << ADC12_TRG_SW_STA_TRG_SW_STA_SHIFT) & ADC12_TRG_SW_STA_TRG_SW_STA_MASK)
#define ADC12_TRG_SW_STA_TRG_SW_STA_GET(x) (((uint32_t)(x) & ADC12_TRG_SW_STA_TRG_SW_STA_MASK) >> ADC12_TRG_SW_STA_TRG_SW_STA_SHIFT)

/*
 * TRIG_SW_INDEX (RW)
 *
 * which trigger for the SW trigger
 * 0 for trig0a, 1 for trig0b…
 * 3 for trig1a, …11 for trig3c
 */
#define ADC12_TRG_SW_STA_TRIG_SW_INDEX_MASK (0xFU)
#define ADC12_TRG_SW_STA_TRIG_SW_INDEX_SHIFT (0U)
#define ADC12_TRG_SW_STA_TRIG_SW_INDEX_SET(x) (((uint32_t)(x) << ADC12_TRG_SW_STA_TRIG_SW_INDEX_SHIFT) & ADC12_TRG_SW_STA_TRIG_SW_INDEX_MASK)
#define ADC12_TRG_SW_STA_TRIG_SW_INDEX_GET(x) (((uint32_t)(x) & ADC12_TRG_SW_STA_TRIG_SW_INDEX_MASK) >> ADC12_TRG_SW_STA_TRIG_SW_INDEX_SHIFT)

/* Bitfield definition for register array: BUS_RESULT */
/*
 * VALID (RO)
 *
 * set after conversion finished if wait_dis is set, cleared after software read.
 * The first time read with 0 will trigger one new conversion.
 * If SW read other channel when one channel conversion is in progress, it will not trigger new conversion at other channel, and will get old result with valid 0, also with read_cflct interrupt status bit set.
 * the result may not realtime if software read once and wait  long time to read again
 */
#define ADC12_BUS_RESULT_VALID_MASK (0x10000UL)
#define ADC12_BUS_RESULT_VALID_SHIFT (16U)
#define ADC12_BUS_RESULT_VALID_GET(x) (((uint32_t)(x) & ADC12_BUS_RESULT_VALID_MASK) >> ADC12_BUS_RESULT_VALID_SHIFT)

/*
 * CHAN_RESULT (RO)
 *
 * read this register will trigger one adc conversion.
 * If wait_dis bit is set, SW will get the latest conversion result(not current one) with valid bit is 0, SW need polling valid bit till it's set to get current result
 * If wait_dis bit is 0, SW can get the current conversion result with holding the bus, valid bit is always set at this mode. this is not recommended if channel sample time is too long
 */
#define ADC12_BUS_RESULT_CHAN_RESULT_MASK (0xFFF0U)
#define ADC12_BUS_RESULT_CHAN_RESULT_SHIFT (4U)
#define ADC12_BUS_RESULT_CHAN_RESULT_GET(x) (((uint32_t)(x) & ADC12_BUS_RESULT_CHAN_RESULT_MASK) >> ADC12_BUS_RESULT_CHAN_RESULT_SHIFT)

/* Bitfield definition for register: BUF_CFG0 */
/*
 * WAIT_DIS (RW)
 *
 * set to disable read waiting, get result immediately but maybe not current conversion result.
 */
#define ADC12_BUF_CFG0_WAIT_DIS_MASK (0x1U)
#define ADC12_BUF_CFG0_WAIT_DIS_SHIFT (0U)
#define ADC12_BUF_CFG0_WAIT_DIS_SET(x) (((uint32_t)(x) << ADC12_BUF_CFG0_WAIT_DIS_SHIFT) & ADC12_BUF_CFG0_WAIT_DIS_MASK)
#define ADC12_BUF_CFG0_WAIT_DIS_GET(x) (((uint32_t)(x) & ADC12_BUF_CFG0_WAIT_DIS_MASK) >> ADC12_BUF_CFG0_WAIT_DIS_SHIFT)

/* Bitfield definition for register: SEQ_CFG0 */
/*
 * CYCLE (RO)
 *
 * current dma write cycle bit
 */
#define ADC12_SEQ_CFG0_CYCLE_MASK (0x80000000UL)
#define ADC12_SEQ_CFG0_CYCLE_SHIFT (31U)
#define ADC12_SEQ_CFG0_CYCLE_GET(x) (((uint32_t)(x) & ADC12_SEQ_CFG0_CYCLE_MASK) >> ADC12_SEQ_CFG0_CYCLE_SHIFT)

/*
 * SEQ_LEN (RW)
 *
 * sequence queue length, 0 for one, 0xF for 16
 */
#define ADC12_SEQ_CFG0_SEQ_LEN_MASK (0xF00U)
#define ADC12_SEQ_CFG0_SEQ_LEN_SHIFT (8U)
#define ADC12_SEQ_CFG0_SEQ_LEN_SET(x) (((uint32_t)(x) << ADC12_SEQ_CFG0_SEQ_LEN_SHIFT) & ADC12_SEQ_CFG0_SEQ_LEN_MASK)
#define ADC12_SEQ_CFG0_SEQ_LEN_GET(x) (((uint32_t)(x) & ADC12_SEQ_CFG0_SEQ_LEN_MASK) >> ADC12_SEQ_CFG0_SEQ_LEN_SHIFT)

/*
 * RESTART_EN (RW)
 *
 * if set together with cont_en, HW will continue process the whole queue after trigger once.
 * If cont_en is 0, this bit is not used
 */
#define ADC12_SEQ_CFG0_RESTART_EN_MASK (0x10U)
#define ADC12_SEQ_CFG0_RESTART_EN_SHIFT (4U)
#define ADC12_SEQ_CFG0_RESTART_EN_SET(x) (((uint32_t)(x) << ADC12_SEQ_CFG0_RESTART_EN_SHIFT) & ADC12_SEQ_CFG0_RESTART_EN_MASK)
#define ADC12_SEQ_CFG0_RESTART_EN_GET(x) (((uint32_t)(x) & ADC12_SEQ_CFG0_RESTART_EN_MASK) >> ADC12_SEQ_CFG0_RESTART_EN_SHIFT)

/*
 * CONT_EN (RW)
 *
 * if set, HW will continue process the queue till end(seq_len) after trigger once
 */
#define ADC12_SEQ_CFG0_CONT_EN_MASK (0x8U)
#define ADC12_SEQ_CFG0_CONT_EN_SHIFT (3U)
#define ADC12_SEQ_CFG0_CONT_EN_SET(x) (((uint32_t)(x) << ADC12_SEQ_CFG0_CONT_EN_SHIFT) & ADC12_SEQ_CFG0_CONT_EN_MASK)
#define ADC12_SEQ_CFG0_CONT_EN_GET(x) (((uint32_t)(x) & ADC12_SEQ_CFG0_CONT_EN_MASK) >> ADC12_SEQ_CFG0_CONT_EN_SHIFT)

/*
 * SW_TRIG (WO)
 *
 * SW trigger, pulse signal, cleared by HW one cycle later
 */
#define ADC12_SEQ_CFG0_SW_TRIG_MASK (0x4U)
#define ADC12_SEQ_CFG0_SW_TRIG_SHIFT (2U)
#define ADC12_SEQ_CFG0_SW_TRIG_SET(x) (((uint32_t)(x) << ADC12_SEQ_CFG0_SW_TRIG_SHIFT) & ADC12_SEQ_CFG0_SW_TRIG_MASK)
#define ADC12_SEQ_CFG0_SW_TRIG_GET(x) (((uint32_t)(x) & ADC12_SEQ_CFG0_SW_TRIG_MASK) >> ADC12_SEQ_CFG0_SW_TRIG_SHIFT)

/*
 * SW_TRIG_EN (RW)
 *
 * set to enable SW trigger
 */
#define ADC12_SEQ_CFG0_SW_TRIG_EN_MASK (0x2U)
#define ADC12_SEQ_CFG0_SW_TRIG_EN_SHIFT (1U)
#define ADC12_SEQ_CFG0_SW_TRIG_EN_SET(x) (((uint32_t)(x) << ADC12_SEQ_CFG0_SW_TRIG_EN_SHIFT) & ADC12_SEQ_CFG0_SW_TRIG_EN_MASK)
#define ADC12_SEQ_CFG0_SW_TRIG_EN_GET(x) (((uint32_t)(x) & ADC12_SEQ_CFG0_SW_TRIG_EN_MASK) >> ADC12_SEQ_CFG0_SW_TRIG_EN_SHIFT)

/*
 * HW_TRIG_EN (RW)
 *
 * set to enable external HW trigger, only trigger on posedge
 */
#define ADC12_SEQ_CFG0_HW_TRIG_EN_MASK (0x1U)
#define ADC12_SEQ_CFG0_HW_TRIG_EN_SHIFT (0U)
#define ADC12_SEQ_CFG0_HW_TRIG_EN_SET(x) (((uint32_t)(x) << ADC12_SEQ_CFG0_HW_TRIG_EN_SHIFT) & ADC12_SEQ_CFG0_HW_TRIG_EN_MASK)
#define ADC12_SEQ_CFG0_HW_TRIG_EN_GET(x) (((uint32_t)(x) & ADC12_SEQ_CFG0_HW_TRIG_EN_MASK) >> ADC12_SEQ_CFG0_HW_TRIG_EN_SHIFT)

/* Bitfield definition for register: SEQ_DMA_ADDR */
/*
 * TAR_ADDR (RW)
 *
 * dma target address, should be 4-byte aligned
 */
#define ADC12_SEQ_DMA_ADDR_TAR_ADDR_MASK (0xFFFFFFFCUL)
#define ADC12_SEQ_DMA_ADDR_TAR_ADDR_SHIFT (2U)
#define ADC12_SEQ_DMA_ADDR_TAR_ADDR_SET(x) (((uint32_t)(x) << ADC12_SEQ_DMA_ADDR_TAR_ADDR_SHIFT) & ADC12_SEQ_DMA_ADDR_TAR_ADDR_MASK)
#define ADC12_SEQ_DMA_ADDR_TAR_ADDR_GET(x) (((uint32_t)(x) & ADC12_SEQ_DMA_ADDR_TAR_ADDR_MASK) >> ADC12_SEQ_DMA_ADDR_TAR_ADDR_SHIFT)

/* Bitfield definition for register: SEQ_WR_ADDR */
/*
 * SEQ_WR_POINTER (RO)
 *
 * HW update this field after each dma write, it indicate the next dma write pointer.
 * dma write address is (tar_addr+seq_wr_pointer)*4
 */
#define ADC12_SEQ_WR_ADDR_SEQ_WR_POINTER_MASK (0xFFFU)
#define ADC12_SEQ_WR_ADDR_SEQ_WR_POINTER_SHIFT (0U)
#define ADC12_SEQ_WR_ADDR_SEQ_WR_POINTER_GET(x) (((uint32_t)(x) & ADC12_SEQ_WR_ADDR_SEQ_WR_POINTER_MASK) >> ADC12_SEQ_WR_ADDR_SEQ_WR_POINTER_SHIFT)

/* Bitfield definition for register: SEQ_DMA_CFG */
/*
 * STOP_POS (RW)
 *
 * if stop_en is set, SW is responsible to udpate this field to the next read point, HW should not write data to this point since it's not read out by SW yet
 */
#define ADC12_SEQ_DMA_CFG_STOP_POS_MASK (0xFFF0000UL)
#define ADC12_SEQ_DMA_CFG_STOP_POS_SHIFT (16U)
#define ADC12_SEQ_DMA_CFG_STOP_POS_SET(x) (((uint32_t)(x) << ADC12_SEQ_DMA_CFG_STOP_POS_SHIFT) & ADC12_SEQ_DMA_CFG_STOP_POS_MASK)
#define ADC12_SEQ_DMA_CFG_STOP_POS_GET(x) (((uint32_t)(x) & ADC12_SEQ_DMA_CFG_STOP_POS_MASK) >> ADC12_SEQ_DMA_CFG_STOP_POS_SHIFT)

/*
 * DMA_RST (RW)
 *
 * set this bit will reset HW dma write pointer to seq_dma_addr, and set HW cycle bit to 1. dma is halted if this bit is set.
 * SW should clear all cycle bit in buffer to 0 before clear dma_rst
 */
#define ADC12_SEQ_DMA_CFG_DMA_RST_MASK (0x2000U)
#define ADC12_SEQ_DMA_CFG_DMA_RST_SHIFT (13U)
#define ADC12_SEQ_DMA_CFG_DMA_RST_SET(x) (((uint32_t)(x) << ADC12_SEQ_DMA_CFG_DMA_RST_SHIFT) & ADC12_SEQ_DMA_CFG_DMA_RST_MASK)
#define ADC12_SEQ_DMA_CFG_DMA_RST_GET(x) (((uint32_t)(x) & ADC12_SEQ_DMA_CFG_DMA_RST_MASK) >> ADC12_SEQ_DMA_CFG_DMA_RST_SHIFT)

/*
 * STOP_EN (RW)
 *
 * set to stop dma if reach the stop_pos
 */
#define ADC12_SEQ_DMA_CFG_STOP_EN_MASK (0x1000U)
#define ADC12_SEQ_DMA_CFG_STOP_EN_SHIFT (12U)
#define ADC12_SEQ_DMA_CFG_STOP_EN_SET(x) (((uint32_t)(x) << ADC12_SEQ_DMA_CFG_STOP_EN_SHIFT) & ADC12_SEQ_DMA_CFG_STOP_EN_MASK)
#define ADC12_SEQ_DMA_CFG_STOP_EN_GET(x) (((uint32_t)(x) & ADC12_SEQ_DMA_CFG_STOP_EN_MASK) >> ADC12_SEQ_DMA_CFG_STOP_EN_SHIFT)

/*
 * BUF_LEN (RW)
 *
 * dma buffer length, after write to (tar_addr[31:2]+buf_len)*4, the next dma address will be tar_addr[31:2]*4
 * 0 for 4byte;
 * 0xFFF for 16kbyte.
 */
#define ADC12_SEQ_DMA_CFG_BUF_LEN_MASK (0xFFFU)
#define ADC12_SEQ_DMA_CFG_BUF_LEN_SHIFT (0U)
#define ADC12_SEQ_DMA_CFG_BUF_LEN_SET(x) (((uint32_t)(x) << ADC12_SEQ_DMA_CFG_BUF_LEN_SHIFT) & ADC12_SEQ_DMA_CFG_BUF_LEN_MASK)
#define ADC12_SEQ_DMA_CFG_BUF_LEN_GET(x) (((uint32_t)(x) & ADC12_SEQ_DMA_CFG_BUF_LEN_MASK) >> ADC12_SEQ_DMA_CFG_BUF_LEN_SHIFT)

/* Bitfield definition for register array: SEQ_QUE */
/*
 * SEQ_INT_EN (RW)
 *
 * interrupt enable for current conversion
 */
#define ADC12_SEQ_QUE_SEQ_INT_EN_MASK (0x20U)
#define ADC12_SEQ_QUE_SEQ_INT_EN_SHIFT (5U)
#define ADC12_SEQ_QUE_SEQ_INT_EN_SET(x) (((uint32_t)(x) << ADC12_SEQ_QUE_SEQ_INT_EN_SHIFT) & ADC12_SEQ_QUE_SEQ_INT_EN_MASK)
#define ADC12_SEQ_QUE_SEQ_INT_EN_GET(x) (((uint32_t)(x) & ADC12_SEQ_QUE_SEQ_INT_EN_MASK) >> ADC12_SEQ_QUE_SEQ_INT_EN_SHIFT)

/*
 * CHAN_NUM_4_0 (RW)
 *
 * channel number for current conversion
 */
#define ADC12_SEQ_QUE_CHAN_NUM_4_0_MASK (0x1FU)
#define ADC12_SEQ_QUE_CHAN_NUM_4_0_SHIFT (0U)
#define ADC12_SEQ_QUE_CHAN_NUM_4_0_SET(x) (((uint32_t)(x) << ADC12_SEQ_QUE_CHAN_NUM_4_0_SHIFT) & ADC12_SEQ_QUE_CHAN_NUM_4_0_MASK)
#define ADC12_SEQ_QUE_CHAN_NUM_4_0_GET(x) (((uint32_t)(x) & ADC12_SEQ_QUE_CHAN_NUM_4_0_MASK) >> ADC12_SEQ_QUE_CHAN_NUM_4_0_SHIFT)

/* Bitfield definition for register of struct array PRD_CFG: PRD_CFG */
/*
 * PRESCALE (RW)
 *
 * 0: 1xclock, 1: 2x, 2: 4x, 3: 8x,…,15: 32768x,…,31: 2Gx
 */
#define ADC12_PRD_CFG_PRD_CFG_PRESCALE_MASK (0x1F00U)
#define ADC12_PRD_CFG_PRD_CFG_PRESCALE_SHIFT (8U)
#define ADC12_PRD_CFG_PRD_CFG_PRESCALE_SET(x) (((uint32_t)(x) << ADC12_PRD_CFG_PRD_CFG_PRESCALE_SHIFT) & ADC12_PRD_CFG_PRD_CFG_PRESCALE_MASK)
#define ADC12_PRD_CFG_PRD_CFG_PRESCALE_GET(x) (((uint32_t)(x) & ADC12_PRD_CFG_PRD_CFG_PRESCALE_MASK) >> ADC12_PRD_CFG_PRD_CFG_PRESCALE_SHIFT)

/*
 * PRD (RW)
 *
 * conver period, with prescale.
 * Set to 0 means disable current channel
 */
#define ADC12_PRD_CFG_PRD_CFG_PRD_MASK (0xFFU)
#define ADC12_PRD_CFG_PRD_CFG_PRD_SHIFT (0U)
#define ADC12_PRD_CFG_PRD_CFG_PRD_SET(x) (((uint32_t)(x) << ADC12_PRD_CFG_PRD_CFG_PRD_SHIFT) & ADC12_PRD_CFG_PRD_CFG_PRD_MASK)
#define ADC12_PRD_CFG_PRD_CFG_PRD_GET(x) (((uint32_t)(x) & ADC12_PRD_CFG_PRD_CFG_PRD_MASK) >> ADC12_PRD_CFG_PRD_CFG_PRD_SHIFT)

/* Bitfield definition for register of struct array PRD_CFG: PRD_THSHD_CFG */
/*
 * THSHDH (RW)
 *
 * threshold high, assert interrupt(if enabled) if result exceed high or low.
 */
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_MASK (0xFFFF0000UL)
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_SHIFT (16U)
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_SET(x) (((uint32_t)(x) << ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_SHIFT) & ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_MASK)
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_GET(x) (((uint32_t)(x) & ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_MASK) >> ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_SHIFT)

/*
 * THSHDL (RW)
 *
 * threshold low
 */
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_MASK (0xFFFFU)
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_SHIFT (0U)
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_SET(x) (((uint32_t)(x) << ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_SHIFT) & ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_MASK)
#define ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_GET(x) (((uint32_t)(x) & ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_MASK) >> ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_SHIFT)

/* Bitfield definition for register of struct array PRD_CFG: PRD_RESULT */
/*
 * CHAN_RESULT (RO)
 *
 * adc convert result, update after each valid conversion.
 * it may be updated period according to config, also may be updated due to other queue convert the same channel
 */
#define ADC12_PRD_CFG_PRD_RESULT_CHAN_RESULT_MASK (0xFFF0U)
#define ADC12_PRD_CFG_PRD_RESULT_CHAN_RESULT_SHIFT (4U)
#define ADC12_PRD_CFG_PRD_RESULT_CHAN_RESULT_GET(x) (((uint32_t)(x) & ADC12_PRD_CFG_PRD_RESULT_CHAN_RESULT_MASK) >> ADC12_PRD_CFG_PRD_RESULT_CHAN_RESULT_SHIFT)

/* Bitfield definition for register array: SAMPLE_CFG */
/*
 * DIFF_SEL (RW)
 *
 * set to 1 to select differential channel
 */
#define ADC12_SAMPLE_CFG_DIFF_SEL_MASK (0x1000U)
#define ADC12_SAMPLE_CFG_DIFF_SEL_SHIFT (12U)
#define ADC12_SAMPLE_CFG_DIFF_SEL_SET(x) (((uint32_t)(x) << ADC12_SAMPLE_CFG_DIFF_SEL_SHIFT) & ADC12_SAMPLE_CFG_DIFF_SEL_MASK)
#define ADC12_SAMPLE_CFG_DIFF_SEL_GET(x) (((uint32_t)(x) & ADC12_SAMPLE_CFG_DIFF_SEL_MASK) >> ADC12_SAMPLE_CFG_DIFF_SEL_SHIFT)

/*
 * SAMPLE_CLOCK_NUMBER_SHIFT (RW)
 *
 * shift for sample_clock_number
 */
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_MASK (0xE00U)
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SHIFT (9U)
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SET(x) (((uint32_t)(x) << ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SHIFT) & ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_MASK)
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_GET(x) (((uint32_t)(x) & ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_MASK) >> ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SHIFT)

/*
 * SAMPLE_CLOCK_NUMBER (RW)
 *
 * sample clock number, base on clock_period, default one period
 */
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_MASK (0x1FFU)
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT (0U)
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SET(x) (((uint32_t)(x) << ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT) & ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_MASK)
#define ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_GET(x) (((uint32_t)(x) & ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_MASK) >> ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT)

/* Bitfield definition for register: CONV_CFG1 */
/*
 * CONVERT_CLOCK_NUMBER (RW)
 *
 * convert clock numbers, set to 13 (0xD) for 12bit mode, which means convert need 14 adc clock cycles(based on clock after divider);
 * set to 11 for 10bit mode; set to 9 for 8bit mode; set to 7 or 6bit mode;
 * Ex: use 200MHz bus clock for adc, set sample_clock_number to 4, sample_clock_number_shift to 0, covert_clk_number to 13 for 12bit mode, clock_divder to 2, then each ADC convertion(plus sample) need 18(14 convert, 4 sample) cycles(66MHz).
 */
#define ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_MASK (0x1F0U)
#define ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_SHIFT (4U)
#define ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_SET(x) (((uint32_t)(x) << ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_SHIFT) & ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_MASK)
#define ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_GET(x) (((uint32_t)(x) & ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_MASK) >> ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_SHIFT)

/*
 * CLOCK_DIVIDER (RW)
 *
 * clock_period, N half clock cycle per half adc cycle
 * 0 for same adc_clk and bus_clk,
 * 1 for 1:2,
 * 2 for 1:3,
 * ...
 * 15 for 1:16
 * Note: set to 2 can genenerate 66.7MHz adc_clk at 200MHz bus_clk
 */
#define ADC12_CONV_CFG1_CLOCK_DIVIDER_MASK (0xFU)
#define ADC12_CONV_CFG1_CLOCK_DIVIDER_SHIFT (0U)
#define ADC12_CONV_CFG1_CLOCK_DIVIDER_SET(x) (((uint32_t)(x) << ADC12_CONV_CFG1_CLOCK_DIVIDER_SHIFT) & ADC12_CONV_CFG1_CLOCK_DIVIDER_MASK)
#define ADC12_CONV_CFG1_CLOCK_DIVIDER_GET(x) (((uint32_t)(x) & ADC12_CONV_CFG1_CLOCK_DIVIDER_MASK) >> ADC12_CONV_CFG1_CLOCK_DIVIDER_SHIFT)

/* Bitfield definition for register: ADC_CFG0 */
/*
 * SEL_SYNC_AHB (RW)
 *
 * set to 1 will enable sync AHB bus, to get better bus performance.
 * Adc_clk must to be set to same as bus clock at this mode
 */
#define ADC12_ADC_CFG0_SEL_SYNC_AHB_MASK (0x80000000UL)
#define ADC12_ADC_CFG0_SEL_SYNC_AHB_SHIFT (31U)
#define ADC12_ADC_CFG0_SEL_SYNC_AHB_SET(x) (((uint32_t)(x) << ADC12_ADC_CFG0_SEL_SYNC_AHB_SHIFT) & ADC12_ADC_CFG0_SEL_SYNC_AHB_MASK)
#define ADC12_ADC_CFG0_SEL_SYNC_AHB_GET(x) (((uint32_t)(x) & ADC12_ADC_CFG0_SEL_SYNC_AHB_MASK) >> ADC12_ADC_CFG0_SEL_SYNC_AHB_SHIFT)

/*
 * ADC_AHB_EN (RW)
 *
 * set to 1 to enable ADC DMA to write data to soc memory bus, for trig queue and seq queue;
 */
#define ADC12_ADC_CFG0_ADC_AHB_EN_MASK (0x20000000UL)
#define ADC12_ADC_CFG0_ADC_AHB_EN_SHIFT (29U)
#define ADC12_ADC_CFG0_ADC_AHB_EN_SET(x) (((uint32_t)(x) << ADC12_ADC_CFG0_ADC_AHB_EN_SHIFT) & ADC12_ADC_CFG0_ADC_AHB_EN_MASK)
#define ADC12_ADC_CFG0_ADC_AHB_EN_GET(x) (((uint32_t)(x) & ADC12_ADC_CFG0_ADC_AHB_EN_MASK) >> ADC12_ADC_CFG0_ADC_AHB_EN_SHIFT)

/* Bitfield definition for register: INT_STS */
/*
 * TRIG_CMPT (W1C)
 *
 * interrupt for one trigger conversion complete if enabled
 */
#define ADC12_INT_STS_TRIG_CMPT_MASK (0x80000000UL)
#define ADC12_INT_STS_TRIG_CMPT_SHIFT (31U)
#define ADC12_INT_STS_TRIG_CMPT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_TRIG_CMPT_SHIFT) & ADC12_INT_STS_TRIG_CMPT_MASK)
#define ADC12_INT_STS_TRIG_CMPT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_TRIG_CMPT_MASK) >> ADC12_INT_STS_TRIG_CMPT_SHIFT)

/*
 * TRIG_SW_CFLCT (W1C)
 *
 */
#define ADC12_INT_STS_TRIG_SW_CFLCT_MASK (0x40000000UL)
#define ADC12_INT_STS_TRIG_SW_CFLCT_SHIFT (30U)
#define ADC12_INT_STS_TRIG_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_TRIG_SW_CFLCT_SHIFT) & ADC12_INT_STS_TRIG_SW_CFLCT_MASK)
#define ADC12_INT_STS_TRIG_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_TRIG_SW_CFLCT_MASK) >> ADC12_INT_STS_TRIG_SW_CFLCT_SHIFT)

/*
 * TRIG_HW_CFLCT (RW)
 *
 */
#define ADC12_INT_STS_TRIG_HW_CFLCT_MASK (0x20000000UL)
#define ADC12_INT_STS_TRIG_HW_CFLCT_SHIFT (29U)
#define ADC12_INT_STS_TRIG_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_TRIG_HW_CFLCT_SHIFT) & ADC12_INT_STS_TRIG_HW_CFLCT_MASK)
#define ADC12_INT_STS_TRIG_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_TRIG_HW_CFLCT_MASK) >> ADC12_INT_STS_TRIG_HW_CFLCT_SHIFT)

/*
 * READ_CFLCT (W1C)
 *
 * read conflict interrup, set if wait_dis is set, one conversion is in progress, SW read another channel
 */
#define ADC12_INT_STS_READ_CFLCT_MASK (0x10000000UL)
#define ADC12_INT_STS_READ_CFLCT_SHIFT (28U)
#define ADC12_INT_STS_READ_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_READ_CFLCT_SHIFT) & ADC12_INT_STS_READ_CFLCT_MASK)
#define ADC12_INT_STS_READ_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_READ_CFLCT_MASK) >> ADC12_INT_STS_READ_CFLCT_SHIFT)

/*
 * SEQ_SW_CFLCT (W1C)
 *
 * sequence queue conflict interrup, set if HW or SW trigger received during conversion
 */
#define ADC12_INT_STS_SEQ_SW_CFLCT_MASK (0x8000000UL)
#define ADC12_INT_STS_SEQ_SW_CFLCT_SHIFT (27U)
#define ADC12_INT_STS_SEQ_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_SEQ_SW_CFLCT_SHIFT) & ADC12_INT_STS_SEQ_SW_CFLCT_MASK)
#define ADC12_INT_STS_SEQ_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_SEQ_SW_CFLCT_MASK) >> ADC12_INT_STS_SEQ_SW_CFLCT_SHIFT)

/*
 * SEQ_HW_CFLCT (RW)
 *
 */
#define ADC12_INT_STS_SEQ_HW_CFLCT_MASK (0x4000000UL)
#define ADC12_INT_STS_SEQ_HW_CFLCT_SHIFT (26U)
#define ADC12_INT_STS_SEQ_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_SEQ_HW_CFLCT_SHIFT) & ADC12_INT_STS_SEQ_HW_CFLCT_MASK)
#define ADC12_INT_STS_SEQ_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_SEQ_HW_CFLCT_MASK) >> ADC12_INT_STS_SEQ_HW_CFLCT_SHIFT)

/*
 * SEQ_DMAABT (W1C)
 *
 * dma abort interrupt, set if seqence dma write pointer reachs sw read pointer if stop_en is set
 */
#define ADC12_INT_STS_SEQ_DMAABT_MASK (0x2000000UL)
#define ADC12_INT_STS_SEQ_DMAABT_SHIFT (25U)
#define ADC12_INT_STS_SEQ_DMAABT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_SEQ_DMAABT_SHIFT) & ADC12_INT_STS_SEQ_DMAABT_MASK)
#define ADC12_INT_STS_SEQ_DMAABT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_SEQ_DMAABT_MASK) >> ADC12_INT_STS_SEQ_DMAABT_SHIFT)

/*
 * SEQ_CMPT (W1C)
 *
 * the whole sequence complete interrupt
 */
#define ADC12_INT_STS_SEQ_CMPT_MASK (0x1000000UL)
#define ADC12_INT_STS_SEQ_CMPT_SHIFT (24U)
#define ADC12_INT_STS_SEQ_CMPT_SET(x) (((uint32_t)(x) << ADC12_INT_STS_SEQ_CMPT_SHIFT) & ADC12_INT_STS_SEQ_CMPT_MASK)
#define ADC12_INT_STS_SEQ_CMPT_GET(x) (((uint32_t)(x) & ADC12_INT_STS_SEQ_CMPT_MASK) >> ADC12_INT_STS_SEQ_CMPT_SHIFT)

/*
 * SEQ_CVC (W1C)
 *
 * one conversion complete in seq_queue if related seq_int_en is set
 */
#define ADC12_INT_STS_SEQ_CVC_MASK (0x800000UL)
#define ADC12_INT_STS_SEQ_CVC_SHIFT (23U)
#define ADC12_INT_STS_SEQ_CVC_SET(x) (((uint32_t)(x) << ADC12_INT_STS_SEQ_CVC_SHIFT) & ADC12_INT_STS_SEQ_CVC_MASK)
#define ADC12_INT_STS_SEQ_CVC_GET(x) (((uint32_t)(x) & ADC12_INT_STS_SEQ_CVC_MASK) >> ADC12_INT_STS_SEQ_CVC_SHIFT)

/*
 * DMA_FIFO_FULL (RW)
 *
 */
#define ADC12_INT_STS_DMA_FIFO_FULL_MASK (0x400000UL)
#define ADC12_INT_STS_DMA_FIFO_FULL_SHIFT (22U)
#define ADC12_INT_STS_DMA_FIFO_FULL_SET(x) (((uint32_t)(x) << ADC12_INT_STS_DMA_FIFO_FULL_SHIFT) & ADC12_INT_STS_DMA_FIFO_FULL_MASK)
#define ADC12_INT_STS_DMA_FIFO_FULL_GET(x) (((uint32_t)(x) & ADC12_INT_STS_DMA_FIFO_FULL_MASK) >> ADC12_INT_STS_DMA_FIFO_FULL_SHIFT)

/*
 * AHB_ERR (RW)
 *
 * set if got hresp=1
 */
#define ADC12_INT_STS_AHB_ERR_MASK (0x200000UL)
#define ADC12_INT_STS_AHB_ERR_SHIFT (21U)
#define ADC12_INT_STS_AHB_ERR_SET(x) (((uint32_t)(x) << ADC12_INT_STS_AHB_ERR_SHIFT) & ADC12_INT_STS_AHB_ERR_MASK)
#define ADC12_INT_STS_AHB_ERR_GET(x) (((uint32_t)(x) & ADC12_INT_STS_AHB_ERR_MASK) >> ADC12_INT_STS_AHB_ERR_SHIFT)

/*
 * WDOG (W1C)
 *
 * set if one chanel watch dog event triggered
 */
#define ADC12_INT_STS_WDOG_MASK (0x7FFFFUL)
#define ADC12_INT_STS_WDOG_SHIFT (0U)
#define ADC12_INT_STS_WDOG_SET(x) (((uint32_t)(x) << ADC12_INT_STS_WDOG_SHIFT) & ADC12_INT_STS_WDOG_MASK)
#define ADC12_INT_STS_WDOG_GET(x) (((uint32_t)(x) & ADC12_INT_STS_WDOG_MASK) >> ADC12_INT_STS_WDOG_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * TRIG_CMPT (W1C)
 *
 * interrupt for one trigger conversion complete if enabled
 */
#define ADC12_INT_EN_TRIG_CMPT_MASK (0x80000000UL)
#define ADC12_INT_EN_TRIG_CMPT_SHIFT (31U)
#define ADC12_INT_EN_TRIG_CMPT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_TRIG_CMPT_SHIFT) & ADC12_INT_EN_TRIG_CMPT_MASK)
#define ADC12_INT_EN_TRIG_CMPT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_TRIG_CMPT_MASK) >> ADC12_INT_EN_TRIG_CMPT_SHIFT)

/*
 * TRIG_SW_CFLCT (W1C)
 *
 */
#define ADC12_INT_EN_TRIG_SW_CFLCT_MASK (0x40000000UL)
#define ADC12_INT_EN_TRIG_SW_CFLCT_SHIFT (30U)
#define ADC12_INT_EN_TRIG_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_TRIG_SW_CFLCT_SHIFT) & ADC12_INT_EN_TRIG_SW_CFLCT_MASK)
#define ADC12_INT_EN_TRIG_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_TRIG_SW_CFLCT_MASK) >> ADC12_INT_EN_TRIG_SW_CFLCT_SHIFT)

/*
 * TRIG_HW_CFLCT (RW)
 *
 */
#define ADC12_INT_EN_TRIG_HW_CFLCT_MASK (0x20000000UL)
#define ADC12_INT_EN_TRIG_HW_CFLCT_SHIFT (29U)
#define ADC12_INT_EN_TRIG_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_TRIG_HW_CFLCT_SHIFT) & ADC12_INT_EN_TRIG_HW_CFLCT_MASK)
#define ADC12_INT_EN_TRIG_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_TRIG_HW_CFLCT_MASK) >> ADC12_INT_EN_TRIG_HW_CFLCT_SHIFT)

/*
 * READ_CFLCT (W1C)
 *
 * read conflict interrup, set if wait_dis is set, one conversion is in progress, SW read another channel
 */
#define ADC12_INT_EN_READ_CFLCT_MASK (0x10000000UL)
#define ADC12_INT_EN_READ_CFLCT_SHIFT (28U)
#define ADC12_INT_EN_READ_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_READ_CFLCT_SHIFT) & ADC12_INT_EN_READ_CFLCT_MASK)
#define ADC12_INT_EN_READ_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_READ_CFLCT_MASK) >> ADC12_INT_EN_READ_CFLCT_SHIFT)

/*
 * SEQ_SW_CFLCT (W1C)
 *
 * sequence queue conflict interrup, set if HW or SW trigger received during conversion
 */
#define ADC12_INT_EN_SEQ_SW_CFLCT_MASK (0x8000000UL)
#define ADC12_INT_EN_SEQ_SW_CFLCT_SHIFT (27U)
#define ADC12_INT_EN_SEQ_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_SEQ_SW_CFLCT_SHIFT) & ADC12_INT_EN_SEQ_SW_CFLCT_MASK)
#define ADC12_INT_EN_SEQ_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_SEQ_SW_CFLCT_MASK) >> ADC12_INT_EN_SEQ_SW_CFLCT_SHIFT)

/*
 * SEQ_HW_CFLCT (RW)
 *
 */
#define ADC12_INT_EN_SEQ_HW_CFLCT_MASK (0x4000000UL)
#define ADC12_INT_EN_SEQ_HW_CFLCT_SHIFT (26U)
#define ADC12_INT_EN_SEQ_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_SEQ_HW_CFLCT_SHIFT) & ADC12_INT_EN_SEQ_HW_CFLCT_MASK)
#define ADC12_INT_EN_SEQ_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_SEQ_HW_CFLCT_MASK) >> ADC12_INT_EN_SEQ_HW_CFLCT_SHIFT)

/*
 * SEQ_DMAABT (W1C)
 *
 * dma abort interrupt, set if seqence dma write pointer reachs sw read pointer if stop_en is set
 */
#define ADC12_INT_EN_SEQ_DMAABT_MASK (0x2000000UL)
#define ADC12_INT_EN_SEQ_DMAABT_SHIFT (25U)
#define ADC12_INT_EN_SEQ_DMAABT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_SEQ_DMAABT_SHIFT) & ADC12_INT_EN_SEQ_DMAABT_MASK)
#define ADC12_INT_EN_SEQ_DMAABT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_SEQ_DMAABT_MASK) >> ADC12_INT_EN_SEQ_DMAABT_SHIFT)

/*
 * SEQ_CMPT (W1C)
 *
 * the whole sequence complete interrupt
 */
#define ADC12_INT_EN_SEQ_CMPT_MASK (0x1000000UL)
#define ADC12_INT_EN_SEQ_CMPT_SHIFT (24U)
#define ADC12_INT_EN_SEQ_CMPT_SET(x) (((uint32_t)(x) << ADC12_INT_EN_SEQ_CMPT_SHIFT) & ADC12_INT_EN_SEQ_CMPT_MASK)
#define ADC12_INT_EN_SEQ_CMPT_GET(x) (((uint32_t)(x) & ADC12_INT_EN_SEQ_CMPT_MASK) >> ADC12_INT_EN_SEQ_CMPT_SHIFT)

/*
 * SEQ_CVC (W1C)
 *
 * one conversion complete in seq_queue if related seq_int_en is set
 */
#define ADC12_INT_EN_SEQ_CVC_MASK (0x800000UL)
#define ADC12_INT_EN_SEQ_CVC_SHIFT (23U)
#define ADC12_INT_EN_SEQ_CVC_SET(x) (((uint32_t)(x) << ADC12_INT_EN_SEQ_CVC_SHIFT) & ADC12_INT_EN_SEQ_CVC_MASK)
#define ADC12_INT_EN_SEQ_CVC_GET(x) (((uint32_t)(x) & ADC12_INT_EN_SEQ_CVC_MASK) >> ADC12_INT_EN_SEQ_CVC_SHIFT)

/*
 * DMA_FIFO_FULL (W1C)
 *
 * DMA fifo full interrupt, user need to check clock frequency if it's set.
 */
#define ADC12_INT_EN_DMA_FIFO_FULL_MASK (0x400000UL)
#define ADC12_INT_EN_DMA_FIFO_FULL_SHIFT (22U)
#define ADC12_INT_EN_DMA_FIFO_FULL_SET(x) (((uint32_t)(x) << ADC12_INT_EN_DMA_FIFO_FULL_SHIFT) & ADC12_INT_EN_DMA_FIFO_FULL_MASK)
#define ADC12_INT_EN_DMA_FIFO_FULL_GET(x) (((uint32_t)(x) & ADC12_INT_EN_DMA_FIFO_FULL_MASK) >> ADC12_INT_EN_DMA_FIFO_FULL_SHIFT)

/*
 * AHB_ERR (W1C)
 *
 * set if got hresp=1, generally caused by wrong trg_dma_addr or seq_dma_addr
 */
#define ADC12_INT_EN_AHB_ERR_MASK (0x200000UL)
#define ADC12_INT_EN_AHB_ERR_SHIFT (21U)
#define ADC12_INT_EN_AHB_ERR_SET(x) (((uint32_t)(x) << ADC12_INT_EN_AHB_ERR_SHIFT) & ADC12_INT_EN_AHB_ERR_MASK)
#define ADC12_INT_EN_AHB_ERR_GET(x) (((uint32_t)(x) & ADC12_INT_EN_AHB_ERR_MASK) >> ADC12_INT_EN_AHB_ERR_SHIFT)

/*
 * WDOG (W1C)
 *
 * set if one chanel watch dog event triggered
 */
#define ADC12_INT_EN_WDOG_MASK (0x7FFFFUL)
#define ADC12_INT_EN_WDOG_SHIFT (0U)
#define ADC12_INT_EN_WDOG_SET(x) (((uint32_t)(x) << ADC12_INT_EN_WDOG_SHIFT) & ADC12_INT_EN_WDOG_MASK)
#define ADC12_INT_EN_WDOG_GET(x) (((uint32_t)(x) & ADC12_INT_EN_WDOG_MASK) >> ADC12_INT_EN_WDOG_SHIFT)

/* Bitfield definition for register: ANA_CTRL0 */
/*
 * CAL_VAL_DIFF (RW)
 *
 * calibration value for differential mode
 */
#define ADC12_ANA_CTRL0_CAL_VAL_DIFF_MASK (0x7F000000UL)
#define ADC12_ANA_CTRL0_CAL_VAL_DIFF_SHIFT (24U)
#define ADC12_ANA_CTRL0_CAL_VAL_DIFF_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_CAL_VAL_DIFF_SHIFT) & ADC12_ANA_CTRL0_CAL_VAL_DIFF_MASK)
#define ADC12_ANA_CTRL0_CAL_VAL_DIFF_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_CAL_VAL_DIFF_MASK) >> ADC12_ANA_CTRL0_CAL_VAL_DIFF_SHIFT)

/*
 * CAL_VAL_SE (RW)
 *
 * calibration value for single-end mode
 */
#define ADC12_ANA_CTRL0_CAL_VAL_SE_MASK (0x7F0000UL)
#define ADC12_ANA_CTRL0_CAL_VAL_SE_SHIFT (16U)
#define ADC12_ANA_CTRL0_CAL_VAL_SE_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_CAL_VAL_SE_SHIFT) & ADC12_ANA_CTRL0_CAL_VAL_SE_MASK)
#define ADC12_ANA_CTRL0_CAL_VAL_SE_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_CAL_VAL_SE_MASK) >> ADC12_ANA_CTRL0_CAL_VAL_SE_SHIFT)

/*
 * REARM_EN (RW)
 *
 * set will insert one adc cycle rearm before sample, user need to increase one to sample_clock_number
 */
#define ADC12_ANA_CTRL0_REARM_EN_MASK (0x4000U)
#define ADC12_ANA_CTRL0_REARM_EN_SHIFT (14U)
#define ADC12_ANA_CTRL0_REARM_EN_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_REARM_EN_SHIFT) & ADC12_ANA_CTRL0_REARM_EN_MASK)
#define ADC12_ANA_CTRL0_REARM_EN_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_REARM_EN_MASK) >> ADC12_ANA_CTRL0_REARM_EN_SHIFT)

/*
 * SELRANGE_LDO (RW)
 *
 * Defines the range for the LDO reference (vdd_soc)
 * selrange_ldo = 0: LDO reference dvdd or vref_ldo in range [0.81;0.99]
 * selrange_ldo = 1: LDO reference dvdd or vref_ldo in range [0.99;1.21]
 */
#define ADC12_ANA_CTRL0_SELRANGE_LDO_MASK (0x800U)
#define ADC12_ANA_CTRL0_SELRANGE_LDO_SHIFT (11U)
#define ADC12_ANA_CTRL0_SELRANGE_LDO_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_SELRANGE_LDO_SHIFT) & ADC12_ANA_CTRL0_SELRANGE_LDO_MASK)
#define ADC12_ANA_CTRL0_SELRANGE_LDO_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_SELRANGE_LDO_MASK) >> ADC12_ANA_CTRL0_SELRANGE_LDO_SHIFT)

/*
 * ENLDO (RW)
 *
 * set to enable adc LDO, need at least 20us for LDO to be stable.
 */
#define ADC12_ANA_CTRL0_ENLDO_MASK (0x40U)
#define ADC12_ANA_CTRL0_ENLDO_SHIFT (6U)
#define ADC12_ANA_CTRL0_ENLDO_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_ENLDO_SHIFT) & ADC12_ANA_CTRL0_ENLDO_MASK)
#define ADC12_ANA_CTRL0_ENLDO_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_ENLDO_MASK) >> ADC12_ANA_CTRL0_ENLDO_SHIFT)

/*
 * ENADC (RW)
 *
 * set to enable adc analog function. user need set it after LDO stable, or wait at least 20us after setting enldo, then set this bit.
 */
#define ADC12_ANA_CTRL0_ENADC_MASK (0x20U)
#define ADC12_ANA_CTRL0_ENADC_SHIFT (5U)
#define ADC12_ANA_CTRL0_ENADC_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_ENADC_SHIFT) & ADC12_ANA_CTRL0_ENADC_MASK)
#define ADC12_ANA_CTRL0_ENADC_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_ENADC_MASK) >> ADC12_ANA_CTRL0_ENADC_SHIFT)

/*
 * RESETADC (RW)
 *
 * set to 1 to reset adc analog; default high.
 */
#define ADC12_ANA_CTRL0_RESETADC_MASK (0x10U)
#define ADC12_ANA_CTRL0_RESETADC_SHIFT (4U)
#define ADC12_ANA_CTRL0_RESETADC_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_RESETADC_SHIFT) & ADC12_ANA_CTRL0_RESETADC_MASK)
#define ADC12_ANA_CTRL0_RESETADC_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_RESETADC_MASK) >> ADC12_ANA_CTRL0_RESETADC_SHIFT)

/*
 * RESETCAL (RW)
 *
 * set to 1 to reset calibration logic; default high.
 */
#define ADC12_ANA_CTRL0_RESETCAL_MASK (0x8U)
#define ADC12_ANA_CTRL0_RESETCAL_SHIFT (3U)
#define ADC12_ANA_CTRL0_RESETCAL_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_RESETCAL_SHIFT) & ADC12_ANA_CTRL0_RESETCAL_MASK)
#define ADC12_ANA_CTRL0_RESETCAL_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_RESETCAL_MASK) >> ADC12_ANA_CTRL0_RESETCAL_SHIFT)

/*
 * STARTCAL (RW)
 *
 * set to start the offset calibration cycle (Active H). user need to clear it after setting it.
 */
#define ADC12_ANA_CTRL0_STARTCAL_MASK (0x4U)
#define ADC12_ANA_CTRL0_STARTCAL_SHIFT (2U)
#define ADC12_ANA_CTRL0_STARTCAL_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_STARTCAL_SHIFT) & ADC12_ANA_CTRL0_STARTCAL_MASK)
#define ADC12_ANA_CTRL0_STARTCAL_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_STARTCAL_MASK) >> ADC12_ANA_CTRL0_STARTCAL_SHIFT)

/*
 * LOADCAL (RW)
 *
 * Signal that loads the offset calibration word into the internal registers (Active H)
 */
#define ADC12_ANA_CTRL0_LOADCAL_MASK (0x2U)
#define ADC12_ANA_CTRL0_LOADCAL_SHIFT (1U)
#define ADC12_ANA_CTRL0_LOADCAL_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL0_LOADCAL_SHIFT) & ADC12_ANA_CTRL0_LOADCAL_MASK)
#define ADC12_ANA_CTRL0_LOADCAL_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL0_LOADCAL_MASK) >> ADC12_ANA_CTRL0_LOADCAL_SHIFT)

/* Bitfield definition for register: ANA_CTRL1 */
/*
 * SELRES (RW)
 *
 * 11-12bit
 * 10-10bit
 * 01-8bit
 * 00-6bit
 */
#define ADC12_ANA_CTRL1_SELRES_MASK (0xC0U)
#define ADC12_ANA_CTRL1_SELRES_SHIFT (6U)
#define ADC12_ANA_CTRL1_SELRES_SET(x) (((uint32_t)(x) << ADC12_ANA_CTRL1_SELRES_SHIFT) & ADC12_ANA_CTRL1_SELRES_MASK)
#define ADC12_ANA_CTRL1_SELRES_GET(x) (((uint32_t)(x) & ADC12_ANA_CTRL1_SELRES_MASK) >> ADC12_ANA_CTRL1_SELRES_SHIFT)

/* Bitfield definition for register: ANA_STATUS */
/*
 * CALON (RW)
 *
 * Indicates if the ADC is in calibration mode (Active H).
 */
#define ADC12_ANA_STATUS_CALON_MASK (0x80U)
#define ADC12_ANA_STATUS_CALON_SHIFT (7U)
#define ADC12_ANA_STATUS_CALON_SET(x) (((uint32_t)(x) << ADC12_ANA_STATUS_CALON_SHIFT) & ADC12_ANA_STATUS_CALON_MASK)
#define ADC12_ANA_STATUS_CALON_GET(x) (((uint32_t)(x) & ADC12_ANA_STATUS_CALON_MASK) >> ADC12_ANA_STATUS_CALON_SHIFT)

/*
 * CAL_OUT (RW)
 *
 */
#define ADC12_ANA_STATUS_CAL_OUT_MASK (0x7FU)
#define ADC12_ANA_STATUS_CAL_OUT_SHIFT (0U)
#define ADC12_ANA_STATUS_CAL_OUT_SET(x) (((uint32_t)(x) << ADC12_ANA_STATUS_CAL_OUT_SHIFT) & ADC12_ANA_STATUS_CAL_OUT_MASK)
#define ADC12_ANA_STATUS_CAL_OUT_GET(x) (((uint32_t)(x) & ADC12_ANA_STATUS_CAL_OUT_MASK) >> ADC12_ANA_STATUS_CAL_OUT_SHIFT)



/* CONFIG register group index macro definition */
#define ADC12_CONFIG_TRG0A (0UL)
#define ADC12_CONFIG_TRG0B (1UL)
#define ADC12_CONFIG_TRG0C (2UL)
#define ADC12_CONFIG_TRG1A (3UL)
#define ADC12_CONFIG_TRG1B (4UL)
#define ADC12_CONFIG_TRG1C (5UL)
#define ADC12_CONFIG_TRG2A (6UL)
#define ADC12_CONFIG_TRG2B (7UL)
#define ADC12_CONFIG_TRG2C (8UL)
#define ADC12_CONFIG_TRG3A (9UL)
#define ADC12_CONFIG_TRG3B (10UL)
#define ADC12_CONFIG_TRG3C (11UL)

/* BUS_RESULT register group index macro definition */
#define ADC12_BUS_RESULT_CHN0 (0UL)
#define ADC12_BUS_RESULT_CHN1 (1UL)
#define ADC12_BUS_RESULT_CHN2 (2UL)
#define ADC12_BUS_RESULT_CHN3 (3UL)
#define ADC12_BUS_RESULT_CHN4 (4UL)
#define ADC12_BUS_RESULT_CHN5 (5UL)
#define ADC12_BUS_RESULT_CHN6 (6UL)
#define ADC12_BUS_RESULT_CHN7 (7UL)
#define ADC12_BUS_RESULT_CHN8 (8UL)
#define ADC12_BUS_RESULT_CHN9 (9UL)
#define ADC12_BUS_RESULT_CHN10 (10UL)
#define ADC12_BUS_RESULT_CHN11 (11UL)
#define ADC12_BUS_RESULT_CHN12 (12UL)
#define ADC12_BUS_RESULT_CHN13 (13UL)
#define ADC12_BUS_RESULT_CHN14 (14UL)
#define ADC12_BUS_RESULT_CHN15 (15UL)
#define ADC12_BUS_RESULT_CHN16 (16UL)
#define ADC12_BUS_RESULT_CHN17 (17UL)
#define ADC12_BUS_RESULT_CHN18 (18UL)

/* SEQ_QUE register group index macro definition */
#define ADC12_SEQ_QUE_CFG0 (0UL)
#define ADC12_SEQ_QUE_CFG1 (1UL)
#define ADC12_SEQ_QUE_CFG2 (2UL)
#define ADC12_SEQ_QUE_CFG3 (3UL)
#define ADC12_SEQ_QUE_CFG4 (4UL)
#define ADC12_SEQ_QUE_CFG5 (5UL)
#define ADC12_SEQ_QUE_CFG6 (6UL)
#define ADC12_SEQ_QUE_CFG7 (7UL)
#define ADC12_SEQ_QUE_CFG8 (8UL)
#define ADC12_SEQ_QUE_CFG9 (9UL)
#define ADC12_SEQ_QUE_CFG10 (10UL)
#define ADC12_SEQ_QUE_CFG11 (11UL)
#define ADC12_SEQ_QUE_CFG12 (12UL)
#define ADC12_SEQ_QUE_CFG13 (13UL)
#define ADC12_SEQ_QUE_CFG14 (14UL)
#define ADC12_SEQ_QUE_CFG15 (15UL)

/* PRD_CFG register group index macro definition */
#define ADC12_PRD_CFG_CHN0 (0UL)
#define ADC12_PRD_CFG_CHN1 (1UL)
#define ADC12_PRD_CFG_CHN2 (2UL)
#define ADC12_PRD_CFG_CHN3 (3UL)
#define ADC12_PRD_CFG_CHN4 (4UL)
#define ADC12_PRD_CFG_CHN5 (5UL)
#define ADC12_PRD_CFG_CHN6 (6UL)
#define ADC12_PRD_CFG_CHN7 (7UL)
#define ADC12_PRD_CFG_CHN8 (8UL)
#define ADC12_PRD_CFG_CHN9 (9UL)
#define ADC12_PRD_CFG_CHN10 (10UL)
#define ADC12_PRD_CFG_CHN11 (11UL)
#define ADC12_PRD_CFG_CHN12 (12UL)
#define ADC12_PRD_CFG_CHN13 (13UL)
#define ADC12_PRD_CFG_CHN14 (14UL)
#define ADC12_PRD_CFG_CHN15 (15UL)
#define ADC12_PRD_CFG_CHN16 (16UL)
#define ADC12_PRD_CFG_CHN17 (17UL)
#define ADC12_PRD_CFG_CHN18 (18UL)

/* SAMPLE_CFG register group index macro definition */
#define ADC12_SAMPLE_CFG_CHN0 (0UL)
#define ADC12_SAMPLE_CFG_CHN1 (1UL)
#define ADC12_SAMPLE_CFG_CHN2 (2UL)
#define ADC12_SAMPLE_CFG_CHN3 (3UL)
#define ADC12_SAMPLE_CFG_CHN4 (4UL)
#define ADC12_SAMPLE_CFG_CHN5 (5UL)
#define ADC12_SAMPLE_CFG_CHN6 (6UL)
#define ADC12_SAMPLE_CFG_CHN7 (7UL)
#define ADC12_SAMPLE_CFG_CHN8 (8UL)
#define ADC12_SAMPLE_CFG_CHN9 (9UL)
#define ADC12_SAMPLE_CFG_CHN10 (10UL)
#define ADC12_SAMPLE_CFG_CHN11 (11UL)
#define ADC12_SAMPLE_CFG_CHN12 (12UL)
#define ADC12_SAMPLE_CFG_CHN13 (13UL)
#define ADC12_SAMPLE_CFG_CHN14 (14UL)
#define ADC12_SAMPLE_CFG_CHN15 (15UL)
#define ADC12_SAMPLE_CFG_CHN16 (16UL)
#define ADC12_SAMPLE_CFG_CHN17 (17UL)
#define ADC12_SAMPLE_CFG_CHN18 (18UL)


#endif /* HPM_ADC12_H */
