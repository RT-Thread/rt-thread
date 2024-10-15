/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_ADC16_H
#define HPM_ADC16_H

typedef struct {
    __RW uint32_t CONFIG[12];                  /* 0x0 - 0x2C:  */
    __RW uint32_t TRG_DMA_ADDR;                /* 0x30:  */
    __RW uint32_t TRG_SW_STA;                  /* 0x34:  */
    __R  uint8_t  RESERVED0[968];              /* 0x38 - 0x3FF: Reserved */
    __R  uint32_t BUS_RESULT[16];              /* 0x400 - 0x43C:  */
    __R  uint8_t  RESERVED1[192];              /* 0x440 - 0x4FF: Reserved */
    __RW uint32_t BUF_CFG0;                    /* 0x500:  */
    __R  uint8_t  RESERVED2[764];              /* 0x504 - 0x7FF: Reserved */
    __RW uint32_t SEQ_CFG0;                    /* 0x800:  */
    __RW uint32_t SEQ_DMA_ADDR;                /* 0x804:  */
    __R  uint32_t SEQ_WR_ADDR;                 /* 0x808:  */
    __RW uint32_t SEQ_DMA_CFG;                 /* 0x80C:  */
    __RW uint32_t SEQ_QUE[16];                 /* 0x810 - 0x84C:  */
    __RW uint32_t SEQ_HIGH_CFG;                /* 0x850:  */
    __R  uint8_t  RESERVED3[940];              /* 0x854 - 0xBFF: Reserved */
    struct {
        __RW uint32_t PRD_CFG;                 /* 0xC00:  */
        __RW uint32_t PRD_THSHD_CFG;           /* 0xC04:  */
        __R  uint32_t PRD_RESULT;              /* 0xC08:  */
        __R  uint8_t  RESERVED0[4];            /* 0xC0C - 0xC0F: Reserved */
    } PRD_CFG[16];
    __R  uint8_t  RESERVED4[768];              /* 0xD00 - 0xFFF: Reserved */
    __RW uint32_t SAMPLE_CFG[16];              /* 0x1000 - 0x103C:  */
    __R  uint8_t  RESERVED5[196];              /* 0x1040 - 0x1103: Reserved */
    __RW uint32_t CONV_CFG1;                   /* 0x1104:  */
    __RW uint32_t ADC_CFG0;                    /* 0x1108:  */
    __R  uint8_t  RESERVED6[4];                /* 0x110C - 0x110F: Reserved */
    __RW uint32_t INT_STS;                     /* 0x1110:  */
    __RW uint32_t INT_EN;                      /* 0x1114:  */
    __R  uint8_t  RESERVED7[232];              /* 0x1118 - 0x11FF: Reserved */
    __RW uint32_t ANA_CTRL0;                   /* 0x1200:  */
    __R  uint8_t  RESERVED8[12];               /* 0x1204 - 0x120F: Reserved */
    __RW uint32_t ANA_STATUS;                  /* 0x1210:  */
    __R  uint8_t  RESERVED9[492];              /* 0x1214 - 0x13FF: Reserved */
    __RW uint16_t ADC16_PARAMS[34];            /* 0x1400 - 0x1442:  */
    __RW uint32_t ADC16_CONFIG0;               /* 0x1444:  */
    __R  uint8_t  RESERVED10[24];              /* 0x1448 - 0x145F: Reserved */
    __RW uint32_t ADC16_CONFIG1;               /* 0x1460:  */
} ADC16_Type;


/* Bitfield definition for register array: CONFIG */
/*
 * TRIG_LEN (WO)
 *
 * length for current trigger, can up to 4 conversions for one trigger, from 0 to 3
 */
#define ADC16_CONFIG_TRIG_LEN_MASK (0xC0000000UL)
#define ADC16_CONFIG_TRIG_LEN_SHIFT (30U)
#define ADC16_CONFIG_TRIG_LEN_SET(x) (((uint32_t)(x) << ADC16_CONFIG_TRIG_LEN_SHIFT) & ADC16_CONFIG_TRIG_LEN_MASK)
#define ADC16_CONFIG_TRIG_LEN_GET(x) (((uint32_t)(x) & ADC16_CONFIG_TRIG_LEN_MASK) >> ADC16_CONFIG_TRIG_LEN_SHIFT)

/*
 * INTEN3 (RW)
 *
 * interrupt enable for 4th conversion
 */
#define ADC16_CONFIG_INTEN3_MASK (0x20000000UL)
#define ADC16_CONFIG_INTEN3_SHIFT (29U)
#define ADC16_CONFIG_INTEN3_SET(x) (((uint32_t)(x) << ADC16_CONFIG_INTEN3_SHIFT) & ADC16_CONFIG_INTEN3_MASK)
#define ADC16_CONFIG_INTEN3_GET(x) (((uint32_t)(x) & ADC16_CONFIG_INTEN3_MASK) >> ADC16_CONFIG_INTEN3_SHIFT)

/*
 * CHAN3 (RW)
 *
 * channel number for 4th conversion
 */
#define ADC16_CONFIG_CHAN3_MASK (0x1F000000UL)
#define ADC16_CONFIG_CHAN3_SHIFT (24U)
#define ADC16_CONFIG_CHAN3_SET(x) (((uint32_t)(x) << ADC16_CONFIG_CHAN3_SHIFT) & ADC16_CONFIG_CHAN3_MASK)
#define ADC16_CONFIG_CHAN3_GET(x) (((uint32_t)(x) & ADC16_CONFIG_CHAN3_MASK) >> ADC16_CONFIG_CHAN3_SHIFT)

/*
 * INTEN2 (RW)
 *
 * interrupt enable for 3rd conversion
 */
#define ADC16_CONFIG_INTEN2_MASK (0x200000UL)
#define ADC16_CONFIG_INTEN2_SHIFT (21U)
#define ADC16_CONFIG_INTEN2_SET(x) (((uint32_t)(x) << ADC16_CONFIG_INTEN2_SHIFT) & ADC16_CONFIG_INTEN2_MASK)
#define ADC16_CONFIG_INTEN2_GET(x) (((uint32_t)(x) & ADC16_CONFIG_INTEN2_MASK) >> ADC16_CONFIG_INTEN2_SHIFT)

/*
 * CHAN2 (RW)
 *
 * channel number for 3rd conversion
 */
#define ADC16_CONFIG_CHAN2_MASK (0x1F0000UL)
#define ADC16_CONFIG_CHAN2_SHIFT (16U)
#define ADC16_CONFIG_CHAN2_SET(x) (((uint32_t)(x) << ADC16_CONFIG_CHAN2_SHIFT) & ADC16_CONFIG_CHAN2_MASK)
#define ADC16_CONFIG_CHAN2_GET(x) (((uint32_t)(x) & ADC16_CONFIG_CHAN2_MASK) >> ADC16_CONFIG_CHAN2_SHIFT)

/*
 * INTEN1 (RW)
 *
 * interrupt enable for 2nd conversion
 */
#define ADC16_CONFIG_INTEN1_MASK (0x2000U)
#define ADC16_CONFIG_INTEN1_SHIFT (13U)
#define ADC16_CONFIG_INTEN1_SET(x) (((uint32_t)(x) << ADC16_CONFIG_INTEN1_SHIFT) & ADC16_CONFIG_INTEN1_MASK)
#define ADC16_CONFIG_INTEN1_GET(x) (((uint32_t)(x) & ADC16_CONFIG_INTEN1_MASK) >> ADC16_CONFIG_INTEN1_SHIFT)

/*
 * CHAN1 (RW)
 *
 * channel number for 2nd conversion
 */
#define ADC16_CONFIG_CHAN1_MASK (0x1F00U)
#define ADC16_CONFIG_CHAN1_SHIFT (8U)
#define ADC16_CONFIG_CHAN1_SET(x) (((uint32_t)(x) << ADC16_CONFIG_CHAN1_SHIFT) & ADC16_CONFIG_CHAN1_MASK)
#define ADC16_CONFIG_CHAN1_GET(x) (((uint32_t)(x) & ADC16_CONFIG_CHAN1_MASK) >> ADC16_CONFIG_CHAN1_SHIFT)

/*
 * QUEUE_EN (RW)
 *
 * preemption queue enable control
 */
#define ADC16_CONFIG_QUEUE_EN_MASK (0x40U)
#define ADC16_CONFIG_QUEUE_EN_SHIFT (6U)
#define ADC16_CONFIG_QUEUE_EN_SET(x) (((uint32_t)(x) << ADC16_CONFIG_QUEUE_EN_SHIFT) & ADC16_CONFIG_QUEUE_EN_MASK)
#define ADC16_CONFIG_QUEUE_EN_GET(x) (((uint32_t)(x) & ADC16_CONFIG_QUEUE_EN_MASK) >> ADC16_CONFIG_QUEUE_EN_SHIFT)

/*
 * INTEN0 (RW)
 *
 * interrupt enable for 1st conversion
 */
#define ADC16_CONFIG_INTEN0_MASK (0x20U)
#define ADC16_CONFIG_INTEN0_SHIFT (5U)
#define ADC16_CONFIG_INTEN0_SET(x) (((uint32_t)(x) << ADC16_CONFIG_INTEN0_SHIFT) & ADC16_CONFIG_INTEN0_MASK)
#define ADC16_CONFIG_INTEN0_GET(x) (((uint32_t)(x) & ADC16_CONFIG_INTEN0_MASK) >> ADC16_CONFIG_INTEN0_SHIFT)

/*
 * CHAN0 (RW)
 *
 * channel number for 1st conversion
 */
#define ADC16_CONFIG_CHAN0_MASK (0x1FU)
#define ADC16_CONFIG_CHAN0_SHIFT (0U)
#define ADC16_CONFIG_CHAN0_SET(x) (((uint32_t)(x) << ADC16_CONFIG_CHAN0_SHIFT) & ADC16_CONFIG_CHAN0_MASK)
#define ADC16_CONFIG_CHAN0_GET(x) (((uint32_t)(x) & ADC16_CONFIG_CHAN0_MASK) >> ADC16_CONFIG_CHAN0_SHIFT)

/* Bitfield definition for register: TRG_DMA_ADDR */
/*
 * TRG_DMA_ADDR (RW)
 *
 * buffer start address for trigger queue, 192byte total, 16 bytes for each trigger (4 bytes for each conversion)
 */
#define ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK (0xFFFFFFFCUL)
#define ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_SHIFT (2U)
#define ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_SET(x) (((uint32_t)(x) << ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_SHIFT) & ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK)
#define ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_GET(x) (((uint32_t)(x) & ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_MASK) >> ADC16_TRG_DMA_ADDR_TRG_DMA_ADDR_SHIFT)

/* Bitfield definition for register: TRG_SW_STA */
/*
 * TRG_SW_STA (RW)
 *
 * SW trigger start bit, HW will clear it after all conversions(up to 4) finished. SW should make sure it's 0 before set it.
 */
#define ADC16_TRG_SW_STA_TRG_SW_STA_MASK (0x10U)
#define ADC16_TRG_SW_STA_TRG_SW_STA_SHIFT (4U)
#define ADC16_TRG_SW_STA_TRG_SW_STA_SET(x) (((uint32_t)(x) << ADC16_TRG_SW_STA_TRG_SW_STA_SHIFT) & ADC16_TRG_SW_STA_TRG_SW_STA_MASK)
#define ADC16_TRG_SW_STA_TRG_SW_STA_GET(x) (((uint32_t)(x) & ADC16_TRG_SW_STA_TRG_SW_STA_MASK) >> ADC16_TRG_SW_STA_TRG_SW_STA_SHIFT)

/*
 * TRIG_SW_INDEX (RW)
 *
 * which trigger for the SW trigger
 * 0 for trig0a, 1 for trig0b…
 * 3 for trig1a, …11 for trig3c
 */
#define ADC16_TRG_SW_STA_TRIG_SW_INDEX_MASK (0xFU)
#define ADC16_TRG_SW_STA_TRIG_SW_INDEX_SHIFT (0U)
#define ADC16_TRG_SW_STA_TRIG_SW_INDEX_SET(x) (((uint32_t)(x) << ADC16_TRG_SW_STA_TRIG_SW_INDEX_SHIFT) & ADC16_TRG_SW_STA_TRIG_SW_INDEX_MASK)
#define ADC16_TRG_SW_STA_TRIG_SW_INDEX_GET(x) (((uint32_t)(x) & ADC16_TRG_SW_STA_TRIG_SW_INDEX_MASK) >> ADC16_TRG_SW_STA_TRIG_SW_INDEX_SHIFT)

/* Bitfield definition for register array: BUS_RESULT */
/*
 * VALID (RO)
 *
 * set after conversion finished if wait_dis is set, cleared after software read.
 * The first time read with 0 will trigger one new conversion.
 * If SW read other channel when one channel conversion is in progress, it will not trigger new conversion at other channel, and will get old result with valid 0, also with read_cflct interrupt status bit set.
 * the result may not realtime if software read once and wait  long time to read again
 */
#define ADC16_BUS_RESULT_VALID_MASK (0x10000UL)
#define ADC16_BUS_RESULT_VALID_SHIFT (16U)
#define ADC16_BUS_RESULT_VALID_GET(x) (((uint32_t)(x) & ADC16_BUS_RESULT_VALID_MASK) >> ADC16_BUS_RESULT_VALID_SHIFT)

/*
 * CHAN_RESULT (RO)
 *
 * read this register will trigger one adc conversion.
 * If wait_dis bit is set, SW will get the latest conversion result(not current one) with valid bit is 0, SW need polling valid bit till it's set to get current result
 * If wait_dis bit is 0, SW can get the current conversion result with holding the bus, valid bit is always set at this mode. this is not recommended if channel sample time is too long
 */
#define ADC16_BUS_RESULT_CHAN_RESULT_MASK (0xFFFFU)
#define ADC16_BUS_RESULT_CHAN_RESULT_SHIFT (0U)
#define ADC16_BUS_RESULT_CHAN_RESULT_GET(x) (((uint32_t)(x) & ADC16_BUS_RESULT_CHAN_RESULT_MASK) >> ADC16_BUS_RESULT_CHAN_RESULT_SHIFT)

/* Bitfield definition for register: BUF_CFG0 */
/*
 * WAIT_DIS (RW)
 *
 * set to disable read waiting, get result immediately but maybe not current conversion result.
 */
#define ADC16_BUF_CFG0_WAIT_DIS_MASK (0x1U)
#define ADC16_BUF_CFG0_WAIT_DIS_SHIFT (0U)
#define ADC16_BUF_CFG0_WAIT_DIS_SET(x) (((uint32_t)(x) << ADC16_BUF_CFG0_WAIT_DIS_SHIFT) & ADC16_BUF_CFG0_WAIT_DIS_MASK)
#define ADC16_BUF_CFG0_WAIT_DIS_GET(x) (((uint32_t)(x) & ADC16_BUF_CFG0_WAIT_DIS_MASK) >> ADC16_BUF_CFG0_WAIT_DIS_SHIFT)

/* Bitfield definition for register: SEQ_CFG0 */
/*
 * CYCLE (RO)
 *
 * current dma write cycle bit
 */
#define ADC16_SEQ_CFG0_CYCLE_MASK (0x80000000UL)
#define ADC16_SEQ_CFG0_CYCLE_SHIFT (31U)
#define ADC16_SEQ_CFG0_CYCLE_GET(x) (((uint32_t)(x) & ADC16_SEQ_CFG0_CYCLE_MASK) >> ADC16_SEQ_CFG0_CYCLE_SHIFT)

/*
 * SEQ_LEN (RW)
 *
 * sequence queue length, 0 for one, 0xF for 16
 */
#define ADC16_SEQ_CFG0_SEQ_LEN_MASK (0xF00U)
#define ADC16_SEQ_CFG0_SEQ_LEN_SHIFT (8U)
#define ADC16_SEQ_CFG0_SEQ_LEN_SET(x) (((uint32_t)(x) << ADC16_SEQ_CFG0_SEQ_LEN_SHIFT) & ADC16_SEQ_CFG0_SEQ_LEN_MASK)
#define ADC16_SEQ_CFG0_SEQ_LEN_GET(x) (((uint32_t)(x) & ADC16_SEQ_CFG0_SEQ_LEN_MASK) >> ADC16_SEQ_CFG0_SEQ_LEN_SHIFT)

/*
 * RESTART_EN (RW)
 *
 * if set together with cont_en, HW will continue process the whole queue after trigger once.
 * If cont_en is 0, this bit is not used
 */
#define ADC16_SEQ_CFG0_RESTART_EN_MASK (0x10U)
#define ADC16_SEQ_CFG0_RESTART_EN_SHIFT (4U)
#define ADC16_SEQ_CFG0_RESTART_EN_SET(x) (((uint32_t)(x) << ADC16_SEQ_CFG0_RESTART_EN_SHIFT) & ADC16_SEQ_CFG0_RESTART_EN_MASK)
#define ADC16_SEQ_CFG0_RESTART_EN_GET(x) (((uint32_t)(x) & ADC16_SEQ_CFG0_RESTART_EN_MASK) >> ADC16_SEQ_CFG0_RESTART_EN_SHIFT)

/*
 * CONT_EN (RW)
 *
 * if set, HW will continue process the queue till end(seq_len) after trigger once
 */
#define ADC16_SEQ_CFG0_CONT_EN_MASK (0x8U)
#define ADC16_SEQ_CFG0_CONT_EN_SHIFT (3U)
#define ADC16_SEQ_CFG0_CONT_EN_SET(x) (((uint32_t)(x) << ADC16_SEQ_CFG0_CONT_EN_SHIFT) & ADC16_SEQ_CFG0_CONT_EN_MASK)
#define ADC16_SEQ_CFG0_CONT_EN_GET(x) (((uint32_t)(x) & ADC16_SEQ_CFG0_CONT_EN_MASK) >> ADC16_SEQ_CFG0_CONT_EN_SHIFT)

/*
 * SW_TRIG (WO)
 *
 * SW trigger, pulse signal, cleared by HW one cycle later
 */
#define ADC16_SEQ_CFG0_SW_TRIG_MASK (0x4U)
#define ADC16_SEQ_CFG0_SW_TRIG_SHIFT (2U)
#define ADC16_SEQ_CFG0_SW_TRIG_SET(x) (((uint32_t)(x) << ADC16_SEQ_CFG0_SW_TRIG_SHIFT) & ADC16_SEQ_CFG0_SW_TRIG_MASK)
#define ADC16_SEQ_CFG0_SW_TRIG_GET(x) (((uint32_t)(x) & ADC16_SEQ_CFG0_SW_TRIG_MASK) >> ADC16_SEQ_CFG0_SW_TRIG_SHIFT)

/*
 * SW_TRIG_EN (RW)
 *
 * set to enable SW trigger
 */
#define ADC16_SEQ_CFG0_SW_TRIG_EN_MASK (0x2U)
#define ADC16_SEQ_CFG0_SW_TRIG_EN_SHIFT (1U)
#define ADC16_SEQ_CFG0_SW_TRIG_EN_SET(x) (((uint32_t)(x) << ADC16_SEQ_CFG0_SW_TRIG_EN_SHIFT) & ADC16_SEQ_CFG0_SW_TRIG_EN_MASK)
#define ADC16_SEQ_CFG0_SW_TRIG_EN_GET(x) (((uint32_t)(x) & ADC16_SEQ_CFG0_SW_TRIG_EN_MASK) >> ADC16_SEQ_CFG0_SW_TRIG_EN_SHIFT)

/*
 * HW_TRIG_EN (RW)
 *
 * set to enable external HW trigger, only trigger on posedge
 */
#define ADC16_SEQ_CFG0_HW_TRIG_EN_MASK (0x1U)
#define ADC16_SEQ_CFG0_HW_TRIG_EN_SHIFT (0U)
#define ADC16_SEQ_CFG0_HW_TRIG_EN_SET(x) (((uint32_t)(x) << ADC16_SEQ_CFG0_HW_TRIG_EN_SHIFT) & ADC16_SEQ_CFG0_HW_TRIG_EN_MASK)
#define ADC16_SEQ_CFG0_HW_TRIG_EN_GET(x) (((uint32_t)(x) & ADC16_SEQ_CFG0_HW_TRIG_EN_MASK) >> ADC16_SEQ_CFG0_HW_TRIG_EN_SHIFT)

/* Bitfield definition for register: SEQ_DMA_ADDR */
/*
 * TAR_ADDR (RW)
 *
 * dma target address, should be 4-byte aligned
 */
#define ADC16_SEQ_DMA_ADDR_TAR_ADDR_MASK (0xFFFFFFFCUL)
#define ADC16_SEQ_DMA_ADDR_TAR_ADDR_SHIFT (2U)
#define ADC16_SEQ_DMA_ADDR_TAR_ADDR_SET(x) (((uint32_t)(x) << ADC16_SEQ_DMA_ADDR_TAR_ADDR_SHIFT) & ADC16_SEQ_DMA_ADDR_TAR_ADDR_MASK)
#define ADC16_SEQ_DMA_ADDR_TAR_ADDR_GET(x) (((uint32_t)(x) & ADC16_SEQ_DMA_ADDR_TAR_ADDR_MASK) >> ADC16_SEQ_DMA_ADDR_TAR_ADDR_SHIFT)

/* Bitfield definition for register: SEQ_WR_ADDR */
/*
 * SEQ_WR_POINTER (RO)
 *
 * HW update this field after each dma write, it indicate the next dma write pointer.
 * dma write address is (tar_addr+seq_wr_pointer)*4
 */
#define ADC16_SEQ_WR_ADDR_SEQ_WR_POINTER_MASK (0xFFFFFFUL)
#define ADC16_SEQ_WR_ADDR_SEQ_WR_POINTER_SHIFT (0U)
#define ADC16_SEQ_WR_ADDR_SEQ_WR_POINTER_GET(x) (((uint32_t)(x) & ADC16_SEQ_WR_ADDR_SEQ_WR_POINTER_MASK) >> ADC16_SEQ_WR_ADDR_SEQ_WR_POINTER_SHIFT)

/* Bitfield definition for register: SEQ_DMA_CFG */
/*
 * STOP_POS (RW)
 *
 * if stop_en is set, SW is responsible to update this field to the next read point, HW should not write data to this point since it's not read out by SW yet
 */
#define ADC16_SEQ_DMA_CFG_STOP_POS_MASK (0xFFF0000UL)
#define ADC16_SEQ_DMA_CFG_STOP_POS_SHIFT (16U)
#define ADC16_SEQ_DMA_CFG_STOP_POS_SET(x) (((uint32_t)(x) << ADC16_SEQ_DMA_CFG_STOP_POS_SHIFT) & ADC16_SEQ_DMA_CFG_STOP_POS_MASK)
#define ADC16_SEQ_DMA_CFG_STOP_POS_GET(x) (((uint32_t)(x) & ADC16_SEQ_DMA_CFG_STOP_POS_MASK) >> ADC16_SEQ_DMA_CFG_STOP_POS_SHIFT)

/*
 * DMA_RST (RW)
 *
 * set this bit will reset HW dma write pointer to seq_dma_addr, and set HW cycle bit to 1. dma is halted if this bit is set.
 * SW should clear all cycle bit in buffer to 0 before clear dma_rst
 */
#define ADC16_SEQ_DMA_CFG_DMA_RST_MASK (0x2000U)
#define ADC16_SEQ_DMA_CFG_DMA_RST_SHIFT (13U)
#define ADC16_SEQ_DMA_CFG_DMA_RST_SET(x) (((uint32_t)(x) << ADC16_SEQ_DMA_CFG_DMA_RST_SHIFT) & ADC16_SEQ_DMA_CFG_DMA_RST_MASK)
#define ADC16_SEQ_DMA_CFG_DMA_RST_GET(x) (((uint32_t)(x) & ADC16_SEQ_DMA_CFG_DMA_RST_MASK) >> ADC16_SEQ_DMA_CFG_DMA_RST_SHIFT)

/*
 * STOP_EN (RW)
 *
 * set to stop dma if reach the stop_pos
 */
#define ADC16_SEQ_DMA_CFG_STOP_EN_MASK (0x1000U)
#define ADC16_SEQ_DMA_CFG_STOP_EN_SHIFT (12U)
#define ADC16_SEQ_DMA_CFG_STOP_EN_SET(x) (((uint32_t)(x) << ADC16_SEQ_DMA_CFG_STOP_EN_SHIFT) & ADC16_SEQ_DMA_CFG_STOP_EN_MASK)
#define ADC16_SEQ_DMA_CFG_STOP_EN_GET(x) (((uint32_t)(x) & ADC16_SEQ_DMA_CFG_STOP_EN_MASK) >> ADC16_SEQ_DMA_CFG_STOP_EN_SHIFT)

/*
 * BUF_LEN (RW)
 *
 * dma buffer length, after write to (tar_addr[31:2]+buf_len)*4, the next dma address will be tar_addr[31:2]*4
 * 0 for 4byte;
 * 0xFFF for 16kbyte.
 */
#define ADC16_SEQ_DMA_CFG_BUF_LEN_MASK (0xFFFU)
#define ADC16_SEQ_DMA_CFG_BUF_LEN_SHIFT (0U)
#define ADC16_SEQ_DMA_CFG_BUF_LEN_SET(x) (((uint32_t)(x) << ADC16_SEQ_DMA_CFG_BUF_LEN_SHIFT) & ADC16_SEQ_DMA_CFG_BUF_LEN_MASK)
#define ADC16_SEQ_DMA_CFG_BUF_LEN_GET(x) (((uint32_t)(x) & ADC16_SEQ_DMA_CFG_BUF_LEN_MASK) >> ADC16_SEQ_DMA_CFG_BUF_LEN_SHIFT)

/* Bitfield definition for register array: SEQ_QUE */
/*
 * SEQ_INT_EN (RW)
 *
 * interrupt enable for current conversion
 */
#define ADC16_SEQ_QUE_SEQ_INT_EN_MASK (0x20U)
#define ADC16_SEQ_QUE_SEQ_INT_EN_SHIFT (5U)
#define ADC16_SEQ_QUE_SEQ_INT_EN_SET(x) (((uint32_t)(x) << ADC16_SEQ_QUE_SEQ_INT_EN_SHIFT) & ADC16_SEQ_QUE_SEQ_INT_EN_MASK)
#define ADC16_SEQ_QUE_SEQ_INT_EN_GET(x) (((uint32_t)(x) & ADC16_SEQ_QUE_SEQ_INT_EN_MASK) >> ADC16_SEQ_QUE_SEQ_INT_EN_SHIFT)

/*
 * CHAN_NUM_4_0 (RW)
 *
 * channel number for current conversion
 */
#define ADC16_SEQ_QUE_CHAN_NUM_4_0_MASK (0x1FU)
#define ADC16_SEQ_QUE_CHAN_NUM_4_0_SHIFT (0U)
#define ADC16_SEQ_QUE_CHAN_NUM_4_0_SET(x) (((uint32_t)(x) << ADC16_SEQ_QUE_CHAN_NUM_4_0_SHIFT) & ADC16_SEQ_QUE_CHAN_NUM_4_0_MASK)
#define ADC16_SEQ_QUE_CHAN_NUM_4_0_GET(x) (((uint32_t)(x) & ADC16_SEQ_QUE_CHAN_NUM_4_0_MASK) >> ADC16_SEQ_QUE_CHAN_NUM_4_0_SHIFT)

/* Bitfield definition for register: SEQ_HIGH_CFG */
/*
 * STOP_POS_HIGH (RW)
 *
 */
#define ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_MASK (0xFFF000UL)
#define ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_SHIFT (12U)
#define ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_SET(x) (((uint32_t)(x) << ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_SHIFT) & ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_MASK)
#define ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_GET(x) (((uint32_t)(x) & ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_MASK) >> ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_SHIFT)

/*
 * BUF_LEN_HIGH (RW)
 *
 */
#define ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_MASK (0xFFFU)
#define ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_SHIFT (0U)
#define ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_SET(x) (((uint32_t)(x) << ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_SHIFT) & ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_MASK)
#define ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_GET(x) (((uint32_t)(x) & ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_MASK) >> ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_SHIFT)

/* Bitfield definition for register of struct array PRD_CFG: PRD_CFG */
/*
 * PRESCALE (RW)
 *
 * 0: 1xclock, 1: 2x, 2: 4x, 3: 8x,…,15: 32768x,…,31: 2Gx
 */
#define ADC16_PRD_CFG_PRD_CFG_PRESCALE_MASK (0x1F00U)
#define ADC16_PRD_CFG_PRD_CFG_PRESCALE_SHIFT (8U)
#define ADC16_PRD_CFG_PRD_CFG_PRESCALE_SET(x) (((uint32_t)(x) << ADC16_PRD_CFG_PRD_CFG_PRESCALE_SHIFT) & ADC16_PRD_CFG_PRD_CFG_PRESCALE_MASK)
#define ADC16_PRD_CFG_PRD_CFG_PRESCALE_GET(x) (((uint32_t)(x) & ADC16_PRD_CFG_PRD_CFG_PRESCALE_MASK) >> ADC16_PRD_CFG_PRD_CFG_PRESCALE_SHIFT)

/*
 * PRD (RW)
 *
 * conver period, with prescale.
 * Set to 0 means disable current channel
 */
#define ADC16_PRD_CFG_PRD_CFG_PRD_MASK (0xFFU)
#define ADC16_PRD_CFG_PRD_CFG_PRD_SHIFT (0U)
#define ADC16_PRD_CFG_PRD_CFG_PRD_SET(x) (((uint32_t)(x) << ADC16_PRD_CFG_PRD_CFG_PRD_SHIFT) & ADC16_PRD_CFG_PRD_CFG_PRD_MASK)
#define ADC16_PRD_CFG_PRD_CFG_PRD_GET(x) (((uint32_t)(x) & ADC16_PRD_CFG_PRD_CFG_PRD_MASK) >> ADC16_PRD_CFG_PRD_CFG_PRD_SHIFT)

/* Bitfield definition for register of struct array PRD_CFG: PRD_THSHD_CFG */
/*
 * THSHDH (RW)
 *
 * threshold high, assert interrupt(if enabled) if result exceed high or low.
 */
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_MASK (0xFFFF0000UL)
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_SHIFT (16U)
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_SET(x) (((uint32_t)(x) << ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_SHIFT) & ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_MASK)
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_GET(x) (((uint32_t)(x) & ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_MASK) >> ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_SHIFT)

/*
 * THSHDL (RW)
 *
 * threshold low
 */
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_MASK (0xFFFFU)
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_SHIFT (0U)
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_SET(x) (((uint32_t)(x) << ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_SHIFT) & ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_MASK)
#define ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_GET(x) (((uint32_t)(x) & ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_MASK) >> ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_SHIFT)

/* Bitfield definition for register of struct array PRD_CFG: PRD_RESULT */
/*
 * CHAN_RESULT (RO)
 *
 * adc convert result, update after each valid conversion.
 * it may be updated period according to config, also may be updated due to other queue convert the same channel
 */
#define ADC16_PRD_CFG_PRD_RESULT_CHAN_RESULT_MASK (0xFFFFU)
#define ADC16_PRD_CFG_PRD_RESULT_CHAN_RESULT_SHIFT (0U)
#define ADC16_PRD_CFG_PRD_RESULT_CHAN_RESULT_GET(x) (((uint32_t)(x) & ADC16_PRD_CFG_PRD_RESULT_CHAN_RESULT_MASK) >> ADC16_PRD_CFG_PRD_RESULT_CHAN_RESULT_SHIFT)

/* Bitfield definition for register array: SAMPLE_CFG */
/*
 * SAMPLE_CLOCK_NUMBER_SHIFT (RW)
 *
 * shift for sample clock number
 */
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_MASK (0xE00U)
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SHIFT (9U)
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SET(x) (((uint32_t)(x) << ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SHIFT) & ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_MASK)
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_GET(x) (((uint32_t)(x) & ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_MASK) >> ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SHIFT)

/*
 * SAMPLE_CLOCK_NUMBER (RW)
 *
 * sample clock number, base on clock_period, default one period
 */
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_MASK (0x1FFU)
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT (0U)
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SET(x) (((uint32_t)(x) << ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT) & ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_MASK)
#define ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_GET(x) (((uint32_t)(x) & ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_MASK) >> ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT)

/* Bitfield definition for register: CONV_CFG1 */
/*
 * CONVERT_CLOCK_NUMBER (RW)
 *
 * convert clock numbers, set to 21 (0x15) for 16bit mode, which means convert need 21 adc clock cycles(based on clock after divider);
 * user can use small value to get faster conversion, but less accuracy, need to config cov_end_cnt at adc16_config1 also.
 * Ex: use 200MHz bus clock for adc, set sample_clock_number to 4, sample_clock_number_shift to 0, covert_clk_number to 21 for 16bit mode, clock_divder to 3, then each ADC conversion(plus sample) need 25 cycles(50MHz).
 */
#define ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_MASK (0x1F0U)
#define ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_SHIFT (4U)
#define ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_SET(x) (((uint32_t)(x) << ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_SHIFT) & ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_MASK)
#define ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_GET(x) (((uint32_t)(x) & ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_MASK) >> ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_SHIFT)

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
#define ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK (0xFU)
#define ADC16_CONV_CFG1_CLOCK_DIVIDER_SHIFT (0U)
#define ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(x) (((uint32_t)(x) << ADC16_CONV_CFG1_CLOCK_DIVIDER_SHIFT) & ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
#define ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(x) (((uint32_t)(x) & ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK) >> ADC16_CONV_CFG1_CLOCK_DIVIDER_SHIFT)

/* Bitfield definition for register: ADC_CFG0 */
/*
 * SEL_SYNC_AHB (RW)
 *
 * set to 1 will enable sync AHB bus, to get better bus performance.
 * Adc_clk must to be set to same as bus clock at this mode
 */
#define ADC16_ADC_CFG0_SEL_SYNC_AHB_MASK (0x80000000UL)
#define ADC16_ADC_CFG0_SEL_SYNC_AHB_SHIFT (31U)
#define ADC16_ADC_CFG0_SEL_SYNC_AHB_SET(x) (((uint32_t)(x) << ADC16_ADC_CFG0_SEL_SYNC_AHB_SHIFT) & ADC16_ADC_CFG0_SEL_SYNC_AHB_MASK)
#define ADC16_ADC_CFG0_SEL_SYNC_AHB_GET(x) (((uint32_t)(x) & ADC16_ADC_CFG0_SEL_SYNC_AHB_MASK) >> ADC16_ADC_CFG0_SEL_SYNC_AHB_SHIFT)

/*
 * ADC_AHB_EN (RW)
 *
 * set to 1 to enable ADC DMA to write data to soc memory bus, for trig queue and seq queue;
 */
#define ADC16_ADC_CFG0_ADC_AHB_EN_MASK (0x20000000UL)
#define ADC16_ADC_CFG0_ADC_AHB_EN_SHIFT (29U)
#define ADC16_ADC_CFG0_ADC_AHB_EN_SET(x) (((uint32_t)(x) << ADC16_ADC_CFG0_ADC_AHB_EN_SHIFT) & ADC16_ADC_CFG0_ADC_AHB_EN_MASK)
#define ADC16_ADC_CFG0_ADC_AHB_EN_GET(x) (((uint32_t)(x) & ADC16_ADC_CFG0_ADC_AHB_EN_MASK) >> ADC16_ADC_CFG0_ADC_AHB_EN_SHIFT)

/*
 * PORT3_REALTIME (RW)
 *
 * set to enable trg queue stop other queues
 */
#define ADC16_ADC_CFG0_PORT3_REALTIME_MASK (0x1U)
#define ADC16_ADC_CFG0_PORT3_REALTIME_SHIFT (0U)
#define ADC16_ADC_CFG0_PORT3_REALTIME_SET(x) (((uint32_t)(x) << ADC16_ADC_CFG0_PORT3_REALTIME_SHIFT) & ADC16_ADC_CFG0_PORT3_REALTIME_MASK)
#define ADC16_ADC_CFG0_PORT3_REALTIME_GET(x) (((uint32_t)(x) & ADC16_ADC_CFG0_PORT3_REALTIME_MASK) >> ADC16_ADC_CFG0_PORT3_REALTIME_SHIFT)

/* Bitfield definition for register: INT_STS */
/*
 * TRIG_CMPT (RW1C)
 *
 * interrupt for one trigger conversion complete if enabled
 */
#define ADC16_INT_STS_TRIG_CMPT_MASK (0x80000000UL)
#define ADC16_INT_STS_TRIG_CMPT_SHIFT (31U)
#define ADC16_INT_STS_TRIG_CMPT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_TRIG_CMPT_SHIFT) & ADC16_INT_STS_TRIG_CMPT_MASK)
#define ADC16_INT_STS_TRIG_CMPT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_TRIG_CMPT_MASK) >> ADC16_INT_STS_TRIG_CMPT_SHIFT)

/*
 * TRIG_SW_CFLCT (RW1C)
 *
 */
#define ADC16_INT_STS_TRIG_SW_CFLCT_MASK (0x40000000UL)
#define ADC16_INT_STS_TRIG_SW_CFLCT_SHIFT (30U)
#define ADC16_INT_STS_TRIG_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_TRIG_SW_CFLCT_SHIFT) & ADC16_INT_STS_TRIG_SW_CFLCT_MASK)
#define ADC16_INT_STS_TRIG_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_TRIG_SW_CFLCT_MASK) >> ADC16_INT_STS_TRIG_SW_CFLCT_SHIFT)

/*
 * TRIG_HW_CFLCT (RW1C)
 *
 */
#define ADC16_INT_STS_TRIG_HW_CFLCT_MASK (0x20000000UL)
#define ADC16_INT_STS_TRIG_HW_CFLCT_SHIFT (29U)
#define ADC16_INT_STS_TRIG_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_TRIG_HW_CFLCT_SHIFT) & ADC16_INT_STS_TRIG_HW_CFLCT_MASK)
#define ADC16_INT_STS_TRIG_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_TRIG_HW_CFLCT_MASK) >> ADC16_INT_STS_TRIG_HW_CFLCT_SHIFT)

/*
 * READ_CFLCT (RW1C)
 *
 * read conflict interrupt, set if wait_dis is set, one conversion is in progress, SW read another channel
 */
#define ADC16_INT_STS_READ_CFLCT_MASK (0x10000000UL)
#define ADC16_INT_STS_READ_CFLCT_SHIFT (28U)
#define ADC16_INT_STS_READ_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_READ_CFLCT_SHIFT) & ADC16_INT_STS_READ_CFLCT_MASK)
#define ADC16_INT_STS_READ_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_READ_CFLCT_MASK) >> ADC16_INT_STS_READ_CFLCT_SHIFT)

/*
 * SEQ_SW_CFLCT (RW1C)
 *
 * sequence queue conflict interrupt, set if HW or SW trigger received during conversion
 */
#define ADC16_INT_STS_SEQ_SW_CFLCT_MASK (0x8000000UL)
#define ADC16_INT_STS_SEQ_SW_CFLCT_SHIFT (27U)
#define ADC16_INT_STS_SEQ_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_SEQ_SW_CFLCT_SHIFT) & ADC16_INT_STS_SEQ_SW_CFLCT_MASK)
#define ADC16_INT_STS_SEQ_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_SEQ_SW_CFLCT_MASK) >> ADC16_INT_STS_SEQ_SW_CFLCT_SHIFT)

/*
 * SEQ_HW_CFLCT (RW1C)
 *
 */
#define ADC16_INT_STS_SEQ_HW_CFLCT_MASK (0x4000000UL)
#define ADC16_INT_STS_SEQ_HW_CFLCT_SHIFT (26U)
#define ADC16_INT_STS_SEQ_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_SEQ_HW_CFLCT_SHIFT) & ADC16_INT_STS_SEQ_HW_CFLCT_MASK)
#define ADC16_INT_STS_SEQ_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_SEQ_HW_CFLCT_MASK) >> ADC16_INT_STS_SEQ_HW_CFLCT_SHIFT)

/*
 * SEQ_DMAABT (RW1C)
 *
 * dma abort interrupt, set if seqence dma write pointer reachs sw read pointer if stop_en is set
 */
#define ADC16_INT_STS_SEQ_DMAABT_MASK (0x2000000UL)
#define ADC16_INT_STS_SEQ_DMAABT_SHIFT (25U)
#define ADC16_INT_STS_SEQ_DMAABT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_SEQ_DMAABT_SHIFT) & ADC16_INT_STS_SEQ_DMAABT_MASK)
#define ADC16_INT_STS_SEQ_DMAABT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_SEQ_DMAABT_MASK) >> ADC16_INT_STS_SEQ_DMAABT_SHIFT)

/*
 * SEQ_CMPT (RW1C)
 *
 * the whole sequence complete interrupt
 */
#define ADC16_INT_STS_SEQ_CMPT_MASK (0x1000000UL)
#define ADC16_INT_STS_SEQ_CMPT_SHIFT (24U)
#define ADC16_INT_STS_SEQ_CMPT_SET(x) (((uint32_t)(x) << ADC16_INT_STS_SEQ_CMPT_SHIFT) & ADC16_INT_STS_SEQ_CMPT_MASK)
#define ADC16_INT_STS_SEQ_CMPT_GET(x) (((uint32_t)(x) & ADC16_INT_STS_SEQ_CMPT_MASK) >> ADC16_INT_STS_SEQ_CMPT_SHIFT)

/*
 * SEQ_CVC (RW1C)
 *
 * one conversion complete in seq_queue if related seq_int_en is set
 */
#define ADC16_INT_STS_SEQ_CVC_MASK (0x800000UL)
#define ADC16_INT_STS_SEQ_CVC_SHIFT (23U)
#define ADC16_INT_STS_SEQ_CVC_SET(x) (((uint32_t)(x) << ADC16_INT_STS_SEQ_CVC_SHIFT) & ADC16_INT_STS_SEQ_CVC_MASK)
#define ADC16_INT_STS_SEQ_CVC_GET(x) (((uint32_t)(x) & ADC16_INT_STS_SEQ_CVC_MASK) >> ADC16_INT_STS_SEQ_CVC_SHIFT)

/*
 * DMA_FIFO_FULL (RW1C)
 *
 * DMA fifo full interrupt, user need to check clock frequency if it's set.
 */
#define ADC16_INT_STS_DMA_FIFO_FULL_MASK (0x400000UL)
#define ADC16_INT_STS_DMA_FIFO_FULL_SHIFT (22U)
#define ADC16_INT_STS_DMA_FIFO_FULL_SET(x) (((uint32_t)(x) << ADC16_INT_STS_DMA_FIFO_FULL_SHIFT) & ADC16_INT_STS_DMA_FIFO_FULL_MASK)
#define ADC16_INT_STS_DMA_FIFO_FULL_GET(x) (((uint32_t)(x) & ADC16_INT_STS_DMA_FIFO_FULL_MASK) >> ADC16_INT_STS_DMA_FIFO_FULL_SHIFT)

/*
 * AHB_ERR (RW1C)
 *
 * set if got hresp=1, generally caused by wrong trg_dma_addr or seq_dma_addr
 */
#define ADC16_INT_STS_AHB_ERR_MASK (0x200000UL)
#define ADC16_INT_STS_AHB_ERR_SHIFT (21U)
#define ADC16_INT_STS_AHB_ERR_SET(x) (((uint32_t)(x) << ADC16_INT_STS_AHB_ERR_SHIFT) & ADC16_INT_STS_AHB_ERR_MASK)
#define ADC16_INT_STS_AHB_ERR_GET(x) (((uint32_t)(x) & ADC16_INT_STS_AHB_ERR_MASK) >> ADC16_INT_STS_AHB_ERR_SHIFT)

/*
 * WDOG (RW1C)
 *
 * set if one chanel watch dog event triggered
 */
#define ADC16_INT_STS_WDOG_MASK (0xFFFFU)
#define ADC16_INT_STS_WDOG_SHIFT (0U)
#define ADC16_INT_STS_WDOG_SET(x) (((uint32_t)(x) << ADC16_INT_STS_WDOG_SHIFT) & ADC16_INT_STS_WDOG_MASK)
#define ADC16_INT_STS_WDOG_GET(x) (((uint32_t)(x) & ADC16_INT_STS_WDOG_MASK) >> ADC16_INT_STS_WDOG_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * TRIG_CMPT (RW)
 *
 * interrupt for one trigger conversion complete if enabled
 */
#define ADC16_INT_EN_TRIG_CMPT_MASK (0x80000000UL)
#define ADC16_INT_EN_TRIG_CMPT_SHIFT (31U)
#define ADC16_INT_EN_TRIG_CMPT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_TRIG_CMPT_SHIFT) & ADC16_INT_EN_TRIG_CMPT_MASK)
#define ADC16_INT_EN_TRIG_CMPT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_TRIG_CMPT_MASK) >> ADC16_INT_EN_TRIG_CMPT_SHIFT)

/*
 * TRIG_SW_CFLCT (RW)
 *
 */
#define ADC16_INT_EN_TRIG_SW_CFLCT_MASK (0x40000000UL)
#define ADC16_INT_EN_TRIG_SW_CFLCT_SHIFT (30U)
#define ADC16_INT_EN_TRIG_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_TRIG_SW_CFLCT_SHIFT) & ADC16_INT_EN_TRIG_SW_CFLCT_MASK)
#define ADC16_INT_EN_TRIG_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_TRIG_SW_CFLCT_MASK) >> ADC16_INT_EN_TRIG_SW_CFLCT_SHIFT)

/*
 * TRIG_HW_CFLCT (RW)
 *
 */
#define ADC16_INT_EN_TRIG_HW_CFLCT_MASK (0x20000000UL)
#define ADC16_INT_EN_TRIG_HW_CFLCT_SHIFT (29U)
#define ADC16_INT_EN_TRIG_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_TRIG_HW_CFLCT_SHIFT) & ADC16_INT_EN_TRIG_HW_CFLCT_MASK)
#define ADC16_INT_EN_TRIG_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_TRIG_HW_CFLCT_MASK) >> ADC16_INT_EN_TRIG_HW_CFLCT_SHIFT)

/*
 * READ_CFLCT (RW)
 *
 * read conflict interrupt, set if wait_dis is set, one conversion is in progress, SW read another channel
 */
#define ADC16_INT_EN_READ_CFLCT_MASK (0x10000000UL)
#define ADC16_INT_EN_READ_CFLCT_SHIFT (28U)
#define ADC16_INT_EN_READ_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_READ_CFLCT_SHIFT) & ADC16_INT_EN_READ_CFLCT_MASK)
#define ADC16_INT_EN_READ_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_READ_CFLCT_MASK) >> ADC16_INT_EN_READ_CFLCT_SHIFT)

/*
 * SEQ_SW_CFLCT (RW)
 *
 * sequence queue conflict interrupt, set if HW or SW trigger received during conversion
 */
#define ADC16_INT_EN_SEQ_SW_CFLCT_MASK (0x8000000UL)
#define ADC16_INT_EN_SEQ_SW_CFLCT_SHIFT (27U)
#define ADC16_INT_EN_SEQ_SW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_SEQ_SW_CFLCT_SHIFT) & ADC16_INT_EN_SEQ_SW_CFLCT_MASK)
#define ADC16_INT_EN_SEQ_SW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_SEQ_SW_CFLCT_MASK) >> ADC16_INT_EN_SEQ_SW_CFLCT_SHIFT)

/*
 * SEQ_HW_CFLCT (RW)
 *
 */
#define ADC16_INT_EN_SEQ_HW_CFLCT_MASK (0x4000000UL)
#define ADC16_INT_EN_SEQ_HW_CFLCT_SHIFT (26U)
#define ADC16_INT_EN_SEQ_HW_CFLCT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_SEQ_HW_CFLCT_SHIFT) & ADC16_INT_EN_SEQ_HW_CFLCT_MASK)
#define ADC16_INT_EN_SEQ_HW_CFLCT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_SEQ_HW_CFLCT_MASK) >> ADC16_INT_EN_SEQ_HW_CFLCT_SHIFT)

/*
 * SEQ_DMAABT (RW)
 *
 * dma abort interrupt, set if seqence dma write pointer reachs sw read pointer if stop_en is set
 */
#define ADC16_INT_EN_SEQ_DMAABT_MASK (0x2000000UL)
#define ADC16_INT_EN_SEQ_DMAABT_SHIFT (25U)
#define ADC16_INT_EN_SEQ_DMAABT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_SEQ_DMAABT_SHIFT) & ADC16_INT_EN_SEQ_DMAABT_MASK)
#define ADC16_INT_EN_SEQ_DMAABT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_SEQ_DMAABT_MASK) >> ADC16_INT_EN_SEQ_DMAABT_SHIFT)

/*
 * SEQ_CMPT (RW)
 *
 * the whole sequence complete interrupt
 */
#define ADC16_INT_EN_SEQ_CMPT_MASK (0x1000000UL)
#define ADC16_INT_EN_SEQ_CMPT_SHIFT (24U)
#define ADC16_INT_EN_SEQ_CMPT_SET(x) (((uint32_t)(x) << ADC16_INT_EN_SEQ_CMPT_SHIFT) & ADC16_INT_EN_SEQ_CMPT_MASK)
#define ADC16_INT_EN_SEQ_CMPT_GET(x) (((uint32_t)(x) & ADC16_INT_EN_SEQ_CMPT_MASK) >> ADC16_INT_EN_SEQ_CMPT_SHIFT)

/*
 * SEQ_CVC (RW)
 *
 * one conversion complete in seq_queue if related seq_int_en is set
 */
#define ADC16_INT_EN_SEQ_CVC_MASK (0x800000UL)
#define ADC16_INT_EN_SEQ_CVC_SHIFT (23U)
#define ADC16_INT_EN_SEQ_CVC_SET(x) (((uint32_t)(x) << ADC16_INT_EN_SEQ_CVC_SHIFT) & ADC16_INT_EN_SEQ_CVC_MASK)
#define ADC16_INT_EN_SEQ_CVC_GET(x) (((uint32_t)(x) & ADC16_INT_EN_SEQ_CVC_MASK) >> ADC16_INT_EN_SEQ_CVC_SHIFT)

/*
 * DMA_FIFO_FULL (RW)
 *
 * DMA fifo full interrupt, user need to check clock frequency if it's set.
 */
#define ADC16_INT_EN_DMA_FIFO_FULL_MASK (0x400000UL)
#define ADC16_INT_EN_DMA_FIFO_FULL_SHIFT (22U)
#define ADC16_INT_EN_DMA_FIFO_FULL_SET(x) (((uint32_t)(x) << ADC16_INT_EN_DMA_FIFO_FULL_SHIFT) & ADC16_INT_EN_DMA_FIFO_FULL_MASK)
#define ADC16_INT_EN_DMA_FIFO_FULL_GET(x) (((uint32_t)(x) & ADC16_INT_EN_DMA_FIFO_FULL_MASK) >> ADC16_INT_EN_DMA_FIFO_FULL_SHIFT)

/*
 * AHB_ERR (RW)
 *
 * set if got hresp=1, generally caused by wrong trg_dma_addr or seq_dma_addr
 */
#define ADC16_INT_EN_AHB_ERR_MASK (0x200000UL)
#define ADC16_INT_EN_AHB_ERR_SHIFT (21U)
#define ADC16_INT_EN_AHB_ERR_SET(x) (((uint32_t)(x) << ADC16_INT_EN_AHB_ERR_SHIFT) & ADC16_INT_EN_AHB_ERR_MASK)
#define ADC16_INT_EN_AHB_ERR_GET(x) (((uint32_t)(x) & ADC16_INT_EN_AHB_ERR_MASK) >> ADC16_INT_EN_AHB_ERR_SHIFT)

/*
 * WDOG (RW)
 *
 * set if one chanel watch dog event triggered
 */
#define ADC16_INT_EN_WDOG_MASK (0xFFFFU)
#define ADC16_INT_EN_WDOG_SHIFT (0U)
#define ADC16_INT_EN_WDOG_SET(x) (((uint32_t)(x) << ADC16_INT_EN_WDOG_SHIFT) & ADC16_INT_EN_WDOG_MASK)
#define ADC16_INT_EN_WDOG_GET(x) (((uint32_t)(x) & ADC16_INT_EN_WDOG_MASK) >> ADC16_INT_EN_WDOG_SHIFT)

/* Bitfield definition for register: ANA_CTRL0 */
/*
 * ADC_CLK_ON (RW)
 *
 * set to enable adc clock to analog, Software should set this bit before access to any adc16_* register.
 * MUST set clock_period to 0 or 1 for adc16 reg access
 */
#define ADC16_ANA_CTRL0_ADC_CLK_ON_MASK (0x1000U)
#define ADC16_ANA_CTRL0_ADC_CLK_ON_SHIFT (12U)
#define ADC16_ANA_CTRL0_ADC_CLK_ON_SET(x) (((uint32_t)(x) << ADC16_ANA_CTRL0_ADC_CLK_ON_SHIFT) & ADC16_ANA_CTRL0_ADC_CLK_ON_MASK)
#define ADC16_ANA_CTRL0_ADC_CLK_ON_GET(x) (((uint32_t)(x) & ADC16_ANA_CTRL0_ADC_CLK_ON_MASK) >> ADC16_ANA_CTRL0_ADC_CLK_ON_SHIFT)

/*
 * STARTCAL (RW)
 *
 * set to start the offset calibration cycle (Active H). user need to clear it after setting it.
 */
#define ADC16_ANA_CTRL0_STARTCAL_MASK (0x4U)
#define ADC16_ANA_CTRL0_STARTCAL_SHIFT (2U)
#define ADC16_ANA_CTRL0_STARTCAL_SET(x) (((uint32_t)(x) << ADC16_ANA_CTRL0_STARTCAL_SHIFT) & ADC16_ANA_CTRL0_STARTCAL_MASK)
#define ADC16_ANA_CTRL0_STARTCAL_GET(x) (((uint32_t)(x) & ADC16_ANA_CTRL0_STARTCAL_MASK) >> ADC16_ANA_CTRL0_STARTCAL_SHIFT)

/* Bitfield definition for register: ANA_STATUS */
/*
 * CALON (RW)
 *
 * Indicates if the ADC is in calibration mode (Active H).
 */
#define ADC16_ANA_STATUS_CALON_MASK (0x80U)
#define ADC16_ANA_STATUS_CALON_SHIFT (7U)
#define ADC16_ANA_STATUS_CALON_SET(x) (((uint32_t)(x) << ADC16_ANA_STATUS_CALON_SHIFT) & ADC16_ANA_STATUS_CALON_MASK)
#define ADC16_ANA_STATUS_CALON_GET(x) (((uint32_t)(x) & ADC16_ANA_STATUS_CALON_MASK) >> ADC16_ANA_STATUS_CALON_SHIFT)

/* Bitfield definition for register array: ADC16_PARAMS */
/*
 * PARAM_VAL (RW)
 *
 */
#define ADC16_ADC16_PARAMS_PARAM_VAL_MASK (0xFFFFU)
#define ADC16_ADC16_PARAMS_PARAM_VAL_SHIFT (0U)
#define ADC16_ADC16_PARAMS_PARAM_VAL_SET(x) (((uint16_t)(x) << ADC16_ADC16_PARAMS_PARAM_VAL_SHIFT) & ADC16_ADC16_PARAMS_PARAM_VAL_MASK)
#define ADC16_ADC16_PARAMS_PARAM_VAL_GET(x) (((uint16_t)(x) & ADC16_ADC16_PARAMS_PARAM_VAL_MASK) >> ADC16_ADC16_PARAMS_PARAM_VAL_SHIFT)

/* Bitfield definition for register: ADC16_CONFIG0 */
/*
 * REG_EN (RW)
 *
 * set to enable regulator
 */
#define ADC16_ADC16_CONFIG0_REG_EN_MASK (0x1000000UL)
#define ADC16_ADC16_CONFIG0_REG_EN_SHIFT (24U)
#define ADC16_ADC16_CONFIG0_REG_EN_SET(x) (((uint32_t)(x) << ADC16_ADC16_CONFIG0_REG_EN_SHIFT) & ADC16_ADC16_CONFIG0_REG_EN_MASK)
#define ADC16_ADC16_CONFIG0_REG_EN_GET(x) (((uint32_t)(x) & ADC16_ADC16_CONFIG0_REG_EN_MASK) >> ADC16_ADC16_CONFIG0_REG_EN_SHIFT)

/*
 * BANDGAP_EN (RW)
 *
 * set to enable bandgap. user should set reg_en and bandgap_en before use adc16.
 */
#define ADC16_ADC16_CONFIG0_BANDGAP_EN_MASK (0x800000UL)
#define ADC16_ADC16_CONFIG0_BANDGAP_EN_SHIFT (23U)
#define ADC16_ADC16_CONFIG0_BANDGAP_EN_SET(x) (((uint32_t)(x) << ADC16_ADC16_CONFIG0_BANDGAP_EN_SHIFT) & ADC16_ADC16_CONFIG0_BANDGAP_EN_MASK)
#define ADC16_ADC16_CONFIG0_BANDGAP_EN_GET(x) (((uint32_t)(x) & ADC16_ADC16_CONFIG0_BANDGAP_EN_MASK) >> ADC16_ADC16_CONFIG0_BANDGAP_EN_SHIFT)

/*
 * CAL_AVG_CFG (RW)
 *
 * for average the calibration result.
 * 0- 1 loop;   1- 2 loops;   2- 4 loops;   3- 8 loops;
 * 4- 16 loops;  5-32 loops;   others reserved
 */
#define ADC16_ADC16_CONFIG0_CAL_AVG_CFG_MASK (0x700000UL)
#define ADC16_ADC16_CONFIG0_CAL_AVG_CFG_SHIFT (20U)
#define ADC16_ADC16_CONFIG0_CAL_AVG_CFG_SET(x) (((uint32_t)(x) << ADC16_ADC16_CONFIG0_CAL_AVG_CFG_SHIFT) & ADC16_ADC16_CONFIG0_CAL_AVG_CFG_MASK)
#define ADC16_ADC16_CONFIG0_CAL_AVG_CFG_GET(x) (((uint32_t)(x) & ADC16_ADC16_CONFIG0_CAL_AVG_CFG_MASK) >> ADC16_ADC16_CONFIG0_CAL_AVG_CFG_SHIFT)

/*
 * PREEMPT_EN (RW)
 *
 * set to enable preemption feature
 */
#define ADC16_ADC16_CONFIG0_PREEMPT_EN_MASK (0x4000U)
#define ADC16_ADC16_CONFIG0_PREEMPT_EN_SHIFT (14U)
#define ADC16_ADC16_CONFIG0_PREEMPT_EN_SET(x) (((uint32_t)(x) << ADC16_ADC16_CONFIG0_PREEMPT_EN_SHIFT) & ADC16_ADC16_CONFIG0_PREEMPT_EN_MASK)
#define ADC16_ADC16_CONFIG0_PREEMPT_EN_GET(x) (((uint32_t)(x) & ADC16_ADC16_CONFIG0_PREEMPT_EN_MASK) >> ADC16_ADC16_CONFIG0_PREEMPT_EN_SHIFT)

/*
 * CONV_PARAM (RW)
 *
 * conversion parameter
 */
#define ADC16_ADC16_CONFIG0_CONV_PARAM_MASK (0x3FFFU)
#define ADC16_ADC16_CONFIG0_CONV_PARAM_SHIFT (0U)
#define ADC16_ADC16_CONFIG0_CONV_PARAM_SET(x) (((uint32_t)(x) << ADC16_ADC16_CONFIG0_CONV_PARAM_SHIFT) & ADC16_ADC16_CONFIG0_CONV_PARAM_MASK)
#define ADC16_ADC16_CONFIG0_CONV_PARAM_GET(x) (((uint32_t)(x) & ADC16_ADC16_CONFIG0_CONV_PARAM_MASK) >> ADC16_ADC16_CONFIG0_CONV_PARAM_SHIFT)

/* Bitfield definition for register: ADC16_CONFIG1 */
/*
 * COV_END_CNT (RW)
 *
 * used for faster conversion, user can change it to get higher convert speed(but less accuracy).
 * should set to (21-convert_clock_number+1).
 */
#define ADC16_ADC16_CONFIG1_COV_END_CNT_MASK (0x1F00U)
#define ADC16_ADC16_CONFIG1_COV_END_CNT_SHIFT (8U)
#define ADC16_ADC16_CONFIG1_COV_END_CNT_SET(x) (((uint32_t)(x) << ADC16_ADC16_CONFIG1_COV_END_CNT_SHIFT) & ADC16_ADC16_CONFIG1_COV_END_CNT_MASK)
#define ADC16_ADC16_CONFIG1_COV_END_CNT_GET(x) (((uint32_t)(x) & ADC16_ADC16_CONFIG1_COV_END_CNT_MASK) >> ADC16_ADC16_CONFIG1_COV_END_CNT_SHIFT)



/* CONFIG register group index macro definition */
#define ADC16_CONFIG_TRG0A (0UL)
#define ADC16_CONFIG_TRG0B (1UL)
#define ADC16_CONFIG_TRG0C (2UL)
#define ADC16_CONFIG_TRG1A (3UL)
#define ADC16_CONFIG_TRG1B (4UL)
#define ADC16_CONFIG_TRG1C (5UL)
#define ADC16_CONFIG_TRG2A (6UL)
#define ADC16_CONFIG_TRG2B (7UL)
#define ADC16_CONFIG_TRG2C (8UL)
#define ADC16_CONFIG_TRG3A (9UL)
#define ADC16_CONFIG_TRG3B (10UL)
#define ADC16_CONFIG_TRG3C (11UL)

/* BUS_RESULT register group index macro definition */
#define ADC16_BUS_RESULT_CHN0 (0UL)
#define ADC16_BUS_RESULT_CHN1 (1UL)
#define ADC16_BUS_RESULT_CHN2 (2UL)
#define ADC16_BUS_RESULT_CHN3 (3UL)
#define ADC16_BUS_RESULT_CHN4 (4UL)
#define ADC16_BUS_RESULT_CHN5 (5UL)
#define ADC16_BUS_RESULT_CHN6 (6UL)
#define ADC16_BUS_RESULT_CHN7 (7UL)
#define ADC16_BUS_RESULT_CHN8 (8UL)
#define ADC16_BUS_RESULT_CHN9 (9UL)
#define ADC16_BUS_RESULT_CHN10 (10UL)
#define ADC16_BUS_RESULT_CHN11 (11UL)
#define ADC16_BUS_RESULT_CHN12 (12UL)
#define ADC16_BUS_RESULT_CHN13 (13UL)
#define ADC16_BUS_RESULT_CHN14 (14UL)
#define ADC16_BUS_RESULT_CHN15 (15UL)

/* SEQ_QUE register group index macro definition */
#define ADC16_SEQ_QUE_CFG0 (0UL)
#define ADC16_SEQ_QUE_CFG1 (1UL)
#define ADC16_SEQ_QUE_CFG2 (2UL)
#define ADC16_SEQ_QUE_CFG3 (3UL)
#define ADC16_SEQ_QUE_CFG4 (4UL)
#define ADC16_SEQ_QUE_CFG5 (5UL)
#define ADC16_SEQ_QUE_CFG6 (6UL)
#define ADC16_SEQ_QUE_CFG7 (7UL)
#define ADC16_SEQ_QUE_CFG8 (8UL)
#define ADC16_SEQ_QUE_CFG9 (9UL)
#define ADC16_SEQ_QUE_CFG10 (10UL)
#define ADC16_SEQ_QUE_CFG11 (11UL)
#define ADC16_SEQ_QUE_CFG12 (12UL)
#define ADC16_SEQ_QUE_CFG13 (13UL)
#define ADC16_SEQ_QUE_CFG14 (14UL)
#define ADC16_SEQ_QUE_CFG15 (15UL)

/* PRD_CFG register group index macro definition */
#define ADC16_PRD_CFG_CHN0 (0UL)
#define ADC16_PRD_CFG_CHN1 (1UL)
#define ADC16_PRD_CFG_CHN2 (2UL)
#define ADC16_PRD_CFG_CHN3 (3UL)
#define ADC16_PRD_CFG_CHN4 (4UL)
#define ADC16_PRD_CFG_CHN5 (5UL)
#define ADC16_PRD_CFG_CHN6 (6UL)
#define ADC16_PRD_CFG_CHN7 (7UL)
#define ADC16_PRD_CFG_CHN8 (8UL)
#define ADC16_PRD_CFG_CHN9 (9UL)
#define ADC16_PRD_CFG_CHN10 (10UL)
#define ADC16_PRD_CFG_CHN11 (11UL)
#define ADC16_PRD_CFG_CHN12 (12UL)
#define ADC16_PRD_CFG_CHN13 (13UL)
#define ADC16_PRD_CFG_CHN14 (14UL)
#define ADC16_PRD_CFG_CHN15 (15UL)

/* SAMPLE_CFG register group index macro definition */
#define ADC16_SAMPLE_CFG_CHN0 (0UL)
#define ADC16_SAMPLE_CFG_CHN1 (1UL)
#define ADC16_SAMPLE_CFG_CHN2 (2UL)
#define ADC16_SAMPLE_CFG_CHN3 (3UL)
#define ADC16_SAMPLE_CFG_CHN4 (4UL)
#define ADC16_SAMPLE_CFG_CHN5 (5UL)
#define ADC16_SAMPLE_CFG_CHN6 (6UL)
#define ADC16_SAMPLE_CFG_CHN7 (7UL)
#define ADC16_SAMPLE_CFG_CHN8 (8UL)
#define ADC16_SAMPLE_CFG_CHN9 (9UL)
#define ADC16_SAMPLE_CFG_CHN10 (10UL)
#define ADC16_SAMPLE_CFG_CHN11 (11UL)
#define ADC16_SAMPLE_CFG_CHN12 (12UL)
#define ADC16_SAMPLE_CFG_CHN13 (13UL)
#define ADC16_SAMPLE_CFG_CHN14 (14UL)
#define ADC16_SAMPLE_CFG_CHN15 (15UL)

/* ADC16_PARAMS register group index macro definition */
#define ADC16_ADC16_PARAMS_ADC16_PARA00 (0UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA01 (1UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA02 (2UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA03 (3UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA04 (4UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA05 (5UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA06 (6UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA07 (7UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA08 (8UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA09 (9UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA10 (10UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA11 (11UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA12 (12UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA13 (13UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA14 (14UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA15 (15UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA16 (16UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA17 (17UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA18 (18UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA19 (19UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA20 (20UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA21 (21UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA22 (22UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA23 (23UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA24 (24UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA25 (25UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA26 (26UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA27 (27UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA28 (28UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA29 (29UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA30 (30UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA31 (31UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA32 (32UL)
#define ADC16_ADC16_PARAMS_ADC16_PARA33 (33UL)


#endif /* HPM_ADC16_H */
