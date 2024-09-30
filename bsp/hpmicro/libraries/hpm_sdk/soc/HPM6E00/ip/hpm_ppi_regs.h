/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PPI_H
#define HPM_PPI_H

typedef struct {
    __RW uint32_t GLB_CFG;                     /* 0x0: glb_cfg */
    __RW uint32_t PAD_CFG;                     /* 0x4: pad_cfg */
    __R  uint8_t  RESERVED0[12];               /* 0x8 - 0x13: Reserved */
    __RW uint32_t CLKPIN_CFG;                  /* 0x14: clkpin_cfg */
    __RW uint32_t TM_CFG;                      /* 0x18: tm_cfg */
    __R  uint8_t  RESERVED1[4];                /* 0x1C - 0x1F: Reserved */
    __RW uint32_t IRQ_STS;                     /* 0x20: irq_sts */
    __RW uint32_t IRQ_EN;                      /* 0x24: irq_en */
    __R  uint8_t  RESERVED2[24];               /* 0x28 - 0x3F: Reserved */
    struct {
        __RW uint32_t CFG0;                    /* 0x40: cfg0 */
        __RW uint32_t CFG1;                    /* 0x44: cfg1 */
        __RW uint32_t CFG2;                    /* 0x48: cfg2 */
        __RW uint32_t CFG3;                    /* 0x4C: cfg3 */
        __RW uint32_t CFG4;                    /* 0x50: cfg4 */
        __R  uint8_t  RESERVED0[12];           /* 0x54 - 0x5F: Reserved */
    } CS[4];
    __R  uint8_t  RESERVED3[832];              /* 0xC0 - 0x3FF: Reserved */
    struct {
        __RW uint32_t CMD_CFG;                 /* 0x400: cmd_cfg */
        __RW uint32_t AD_CFG;                  /* 0x404: ad_cfg */
        __RW uint32_t CTRL_CFG;                /* 0x408: ctrl_cfg */
        __R  uint8_t  RESERVED0[4];            /* 0x40C - 0x40F: Reserved */
    } CMD[64];
} PPI_Type;


/* Bitfield definition for register: GLB_CFG */
/*
 * PAD_OUT_REG_ENJ (RW)
 *
 * 0:  register output, one cycle delay;
 * 1:  direct output， no delay but may have timing issue
 */
#define PPI_GLB_CFG_PAD_OUT_REG_ENJ_MASK (0x2U)
#define PPI_GLB_CFG_PAD_OUT_REG_ENJ_SHIFT (1U)
#define PPI_GLB_CFG_PAD_OUT_REG_ENJ_SET(x) (((uint32_t)(x) << PPI_GLB_CFG_PAD_OUT_REG_ENJ_SHIFT) & PPI_GLB_CFG_PAD_OUT_REG_ENJ_MASK)
#define PPI_GLB_CFG_PAD_OUT_REG_ENJ_GET(x) (((uint32_t)(x) & PPI_GLB_CFG_PAD_OUT_REG_ENJ_MASK) >> PPI_GLB_CFG_PAD_OUT_REG_ENJ_SHIFT)

/*
 * SOFT_RESET (RW)
 *
 * software reset
 */
#define PPI_GLB_CFG_SOFT_RESET_MASK (0x1U)
#define PPI_GLB_CFG_SOFT_RESET_SHIFT (0U)
#define PPI_GLB_CFG_SOFT_RESET_SET(x) (((uint32_t)(x) << PPI_GLB_CFG_SOFT_RESET_SHIFT) & PPI_GLB_CFG_SOFT_RESET_MASK)
#define PPI_GLB_CFG_SOFT_RESET_GET(x) (((uint32_t)(x) & PPI_GLB_CFG_SOFT_RESET_MASK) >> PPI_GLB_CFG_SOFT_RESET_SHIFT)

/* Bitfield definition for register: PAD_CFG */
/*
 * CS_IDLE_ST (RW)
 *
 * cs pin idle state, default high for active low
 */
#define PPI_PAD_CFG_CS_IDLE_ST_MASK (0xF000000UL)
#define PPI_PAD_CFG_CS_IDLE_ST_SHIFT (24U)
#define PPI_PAD_CFG_CS_IDLE_ST_SET(x) (((uint32_t)(x) << PPI_PAD_CFG_CS_IDLE_ST_SHIFT) & PPI_PAD_CFG_CS_IDLE_ST_MASK)
#define PPI_PAD_CFG_CS_IDLE_ST_GET(x) (((uint32_t)(x) & PPI_PAD_CFG_CS_IDLE_ST_MASK) >> PPI_PAD_CFG_CS_IDLE_ST_SHIFT)

/*
 * DM_PAD_POL (RW)
 *
 * dm pin polarity
 */
#define PPI_PAD_CFG_DM_PAD_POL_MASK (0xF0000UL)
#define PPI_PAD_CFG_DM_PAD_POL_SHIFT (16U)
#define PPI_PAD_CFG_DM_PAD_POL_SET(x) (((uint32_t)(x) << PPI_PAD_CFG_DM_PAD_POL_SHIFT) & PPI_PAD_CFG_DM_PAD_POL_MASK)
#define PPI_PAD_CFG_DM_PAD_POL_GET(x) (((uint32_t)(x) & PPI_PAD_CFG_DM_PAD_POL_MASK) >> PPI_PAD_CFG_DM_PAD_POL_SHIFT)

/*
 * CTRL_PAD_OE (RW)
 *
 * the pad output enable signal. 0 for IN; 1 for OUT.
 * NOTE: for unused pads, set both ctrl_pad_oe and ctrl_pad_pol to 0
 */
#define PPI_PAD_CFG_CTRL_PAD_OE_MASK (0xFF00U)
#define PPI_PAD_CFG_CTRL_PAD_OE_SHIFT (8U)
#define PPI_PAD_CFG_CTRL_PAD_OE_SET(x) (((uint32_t)(x) << PPI_PAD_CFG_CTRL_PAD_OE_SHIFT) & PPI_PAD_CFG_CTRL_PAD_OE_MASK)
#define PPI_PAD_CFG_CTRL_PAD_OE_GET(x) (((uint32_t)(x) & PPI_PAD_CFG_CTRL_PAD_OE_MASK) >> PPI_PAD_CFG_CTRL_PAD_OE_SHIFT)

/*
 * CTRL_PAD_POL (RW)
 *
 * for OUT pad:
 * 0: output the value in cmd
 * 1: output reversed value in cmd
 * for IN pad, defines the signal active value,  when ctrl_cfg.io_cfg is set,
 * will wait the active value for ready(generally read or write ready)
 */
#define PPI_PAD_CFG_CTRL_PAD_POL_MASK (0xFFU)
#define PPI_PAD_CFG_CTRL_PAD_POL_SHIFT (0U)
#define PPI_PAD_CFG_CTRL_PAD_POL_SET(x) (((uint32_t)(x) << PPI_PAD_CFG_CTRL_PAD_POL_SHIFT) & PPI_PAD_CFG_CTRL_PAD_POL_MASK)
#define PPI_PAD_CFG_CTRL_PAD_POL_GET(x) (((uint32_t)(x) & PPI_PAD_CFG_CTRL_PAD_POL_MASK) >> PPI_PAD_CFG_CTRL_PAD_POL_SHIFT)

/* Bitfield definition for register: CLKPIN_CFG */
/*
 * CYCLE (RW)
 *
 * there will be a system counter run from 0 to cycle,
 * clk output will be set to high when counter is clk_high, and low when counter is clk_low.
 * The output will be system clock if cycle is 0.
 * All 4 CS share same clock configuration(one clock pin with configured frequency).
 * different CS can be assert at different  counter value.
 */
#define PPI_CLKPIN_CFG_CYCLE_MASK (0xF000000UL)
#define PPI_CLKPIN_CFG_CYCLE_SHIFT (24U)
#define PPI_CLKPIN_CFG_CYCLE_SET(x) (((uint32_t)(x) << PPI_CLKPIN_CFG_CYCLE_SHIFT) & PPI_CLKPIN_CFG_CYCLE_MASK)
#define PPI_CLKPIN_CFG_CYCLE_GET(x) (((uint32_t)(x) & PPI_CLKPIN_CFG_CYCLE_MASK) >> PPI_CLKPIN_CFG_CYCLE_SHIFT)

/*
 * HIGH (RW)
 *
 * clock high numer
 */
#define PPI_CLKPIN_CFG_HIGH_MASK (0xF0000UL)
#define PPI_CLKPIN_CFG_HIGH_SHIFT (16U)
#define PPI_CLKPIN_CFG_HIGH_SET(x) (((uint32_t)(x) << PPI_CLKPIN_CFG_HIGH_SHIFT) & PPI_CLKPIN_CFG_HIGH_MASK)
#define PPI_CLKPIN_CFG_HIGH_GET(x) (((uint32_t)(x) & PPI_CLKPIN_CFG_HIGH_MASK) >> PPI_CLKPIN_CFG_HIGH_SHIFT)

/*
 * LOW (RW)
 *
 * clock low number
 */
#define PPI_CLKPIN_CFG_LOW_MASK (0xF00U)
#define PPI_CLKPIN_CFG_LOW_SHIFT (8U)
#define PPI_CLKPIN_CFG_LOW_SET(x) (((uint32_t)(x) << PPI_CLKPIN_CFG_LOW_SHIFT) & PPI_CLKPIN_CFG_LOW_MASK)
#define PPI_CLKPIN_CFG_LOW_GET(x) (((uint32_t)(x) & PPI_CLKPIN_CFG_LOW_MASK) >> PPI_CLKPIN_CFG_LOW_SHIFT)

/*
 * INVERT (RW)
 *
 * set to invert clock output
 */
#define PPI_CLKPIN_CFG_INVERT_MASK (0x20U)
#define PPI_CLKPIN_CFG_INVERT_SHIFT (5U)
#define PPI_CLKPIN_CFG_INVERT_SET(x) (((uint32_t)(x) << PPI_CLKPIN_CFG_INVERT_SHIFT) & PPI_CLKPIN_CFG_INVERT_MASK)
#define PPI_CLKPIN_CFG_INVERT_GET(x) (((uint32_t)(x) & PPI_CLKPIN_CFG_INVERT_MASK) >> PPI_CLKPIN_CFG_INVERT_SHIFT)

/*
 * AON (RW)
 *
 * 0:  use clk_gate in cmd sequence for whether output clock
 * 1: always enable clock output;
 */
#define PPI_CLKPIN_CFG_AON_MASK (0x2U)
#define PPI_CLKPIN_CFG_AON_SHIFT (1U)
#define PPI_CLKPIN_CFG_AON_SET(x) (((uint32_t)(x) << PPI_CLKPIN_CFG_AON_SHIFT) & PPI_CLKPIN_CFG_AON_MASK)
#define PPI_CLKPIN_CFG_AON_GET(x) (((uint32_t)(x) & PPI_CLKPIN_CFG_AON_MASK) >> PPI_CLKPIN_CFG_AON_SHIFT)

/*
 * EN (RW)
 *
 * set to enable clock logic
 */
#define PPI_CLKPIN_CFG_EN_MASK (0x1U)
#define PPI_CLKPIN_CFG_EN_SHIFT (0U)
#define PPI_CLKPIN_CFG_EN_SET(x) (((uint32_t)(x) << PPI_CLKPIN_CFG_EN_SHIFT) & PPI_CLKPIN_CFG_EN_MASK)
#define PPI_CLKPIN_CFG_EN_GET(x) (((uint32_t)(x) & PPI_CLKPIN_CFG_EN_MASK) >> PPI_CLKPIN_CFG_EN_SHIFT)

/* Bitfield definition for register: TM_CFG */
/*
 * TM_EN (RW)
 *
 * timeout enable.
 * if enabled, then if each AHB transfer time exceed tm_cfg clock cycles, will assert irq
 */
#define PPI_TM_CFG_TM_EN_MASK (0x10000UL)
#define PPI_TM_CFG_TM_EN_SHIFT (16U)
#define PPI_TM_CFG_TM_EN_SET(x) (((uint32_t)(x) << PPI_TM_CFG_TM_EN_SHIFT) & PPI_TM_CFG_TM_EN_MASK)
#define PPI_TM_CFG_TM_EN_GET(x) (((uint32_t)(x) & PPI_TM_CFG_TM_EN_MASK) >> PPI_TM_CFG_TM_EN_SHIFT)

/*
 * TM_CFG (RW)
 *
 * timeout value, max 20us at 200MHz clock
 */
#define PPI_TM_CFG_TM_CFG_MASK (0xFFFU)
#define PPI_TM_CFG_TM_CFG_SHIFT (0U)
#define PPI_TM_CFG_TM_CFG_SET(x) (((uint32_t)(x) << PPI_TM_CFG_TM_CFG_SHIFT) & PPI_TM_CFG_TM_CFG_MASK)
#define PPI_TM_CFG_TM_CFG_GET(x) (((uint32_t)(x) & PPI_TM_CFG_TM_CFG_MASK) >> PPI_TM_CFG_TM_CFG_SHIFT)

/* Bitfield definition for register: IRQ_STS */
/*
 * IRQ_TMOUT_STS (RW1C)
 *
 * tiemout interrupt status, write 1 to clear
 */
#define PPI_IRQ_STS_IRQ_TMOUT_STS_MASK (0x1U)
#define PPI_IRQ_STS_IRQ_TMOUT_STS_SHIFT (0U)
#define PPI_IRQ_STS_IRQ_TMOUT_STS_SET(x) (((uint32_t)(x) << PPI_IRQ_STS_IRQ_TMOUT_STS_SHIFT) & PPI_IRQ_STS_IRQ_TMOUT_STS_MASK)
#define PPI_IRQ_STS_IRQ_TMOUT_STS_GET(x) (((uint32_t)(x) & PPI_IRQ_STS_IRQ_TMOUT_STS_MASK) >> PPI_IRQ_STS_IRQ_TMOUT_STS_SHIFT)

/* Bitfield definition for register: IRQ_EN */
/*
 * IRQ_TMOUT_EN (RW)
 *
 * timeout interrupt enable
 */
#define PPI_IRQ_EN_IRQ_TMOUT_EN_MASK (0x1U)
#define PPI_IRQ_EN_IRQ_TMOUT_EN_SHIFT (0U)
#define PPI_IRQ_EN_IRQ_TMOUT_EN_SET(x) (((uint32_t)(x) << PPI_IRQ_EN_IRQ_TMOUT_EN_SHIFT) & PPI_IRQ_EN_IRQ_TMOUT_EN_MASK)
#define PPI_IRQ_EN_IRQ_TMOUT_EN_GET(x) (((uint32_t)(x) & PPI_IRQ_EN_IRQ_TMOUT_EN_MASK) >> PPI_IRQ_EN_IRQ_TMOUT_EN_SHIFT)

/* Bitfield definition for register of struct array CS: CFG0 */
/*
 * ADDR_END (RW)
 *
 */
#define PPI_CS_CFG0_ADDR_END_MASK (0xFFF0000UL)
#define PPI_CS_CFG0_ADDR_END_SHIFT (16U)
#define PPI_CS_CFG0_ADDR_END_SET(x) (((uint32_t)(x) << PPI_CS_CFG0_ADDR_END_SHIFT) & PPI_CS_CFG0_ADDR_END_MASK)
#define PPI_CS_CFG0_ADDR_END_GET(x) (((uint32_t)(x) & PPI_CS_CFG0_ADDR_END_MASK) >> PPI_CS_CFG0_ADDR_END_SHIFT)

/*
 * ADDR_START (RW)
 *
 * addr_start and addr_end config the address slot for CS0, use high 12bit,
 * the minimun slot is 1Mbyte(addr_start==addr_end)
 */
#define PPI_CS_CFG0_ADDR_START_MASK (0xFFFU)
#define PPI_CS_CFG0_ADDR_START_SHIFT (0U)
#define PPI_CS_CFG0_ADDR_START_SET(x) (((uint32_t)(x) << PPI_CS_CFG0_ADDR_START_SHIFT) & PPI_CS_CFG0_ADDR_START_MASK)
#define PPI_CS_CFG0_ADDR_START_GET(x) (((uint32_t)(x) & PPI_CS_CFG0_ADDR_START_MASK) >> PPI_CS_CFG0_ADDR_START_SHIFT)

/* Bitfield definition for register of struct array CS: CFG1 */
/*
 * ADDR_MASK (RW)
 *
 * the high AHB address will AND with {cs0_mask[15:0], 16'hFFFF},
 * shift right with addr_shift, then output as real address.
 */
#define PPI_CS_CFG1_ADDR_MASK_MASK (0xFFFF0000UL)
#define PPI_CS_CFG1_ADDR_MASK_SHIFT (16U)
#define PPI_CS_CFG1_ADDR_MASK_SET(x) (((uint32_t)(x) << PPI_CS_CFG1_ADDR_MASK_SHIFT) & PPI_CS_CFG1_ADDR_MASK_MASK)
#define PPI_CS_CFG1_ADDR_MASK_GET(x) (((uint32_t)(x) & PPI_CS_CFG1_ADDR_MASK_MASK) >> PPI_CS_CFG1_ADDR_MASK_SHIFT)

/*
 * ADDR_SHIFT (RW)
 *
 * gennerally should be configured according to port size,
 * 0 for 8bit; 1 for 16bit; 2 for 32bit;
 */
#define PPI_CS_CFG1_ADDR_SHIFT_MASK (0xFU)
#define PPI_CS_CFG1_ADDR_SHIFT_SHIFT (0U)
#define PPI_CS_CFG1_ADDR_SHIFT_SET(x) (((uint32_t)(x) << PPI_CS_CFG1_ADDR_SHIFT_SHIFT) & PPI_CS_CFG1_ADDR_SHIFT_MASK)
#define PPI_CS_CFG1_ADDR_SHIFT_GET(x) (((uint32_t)(x) & PPI_CS_CFG1_ADDR_SHIFT_MASK) >> PPI_CS_CFG1_ADDR_SHIFT_SHIFT)

/* Bitfield definition for register of struct array CS: CFG2 */
/*
 * CS_SYNC_EN (RW)
 *
 * set to enable CS pin sync with clock counter.
 * Clr if use async mode(no clk pin), or not care the CS start time with clk pin
 */
#define PPI_CS_CFG2_CS_SYNC_EN_MASK (0x10000000UL)
#define PPI_CS_CFG2_CS_SYNC_EN_SHIFT (28U)
#define PPI_CS_CFG2_CS_SYNC_EN_SET(x) (((uint32_t)(x) << PPI_CS_CFG2_CS_SYNC_EN_SHIFT) & PPI_CS_CFG2_CS_SYNC_EN_MASK)
#define PPI_CS_CFG2_CS_SYNC_EN_GET(x) (((uint32_t)(x) & PPI_CS_CFG2_CS_SYNC_EN_MASK) >> PPI_CS_CFG2_CS_SYNC_EN_SHIFT)

/*
 * SYNC_CLK_SEL (RW)
 *
 * CS assert at when clk_div_cnt equal to sync_clk_sel
 */
#define PPI_CS_CFG2_SYNC_CLK_SEL_MASK (0xF00000UL)
#define PPI_CS_CFG2_SYNC_CLK_SEL_SHIFT (20U)
#define PPI_CS_CFG2_SYNC_CLK_SEL_SET(x) (((uint32_t)(x) << PPI_CS_CFG2_SYNC_CLK_SEL_SHIFT) & PPI_CS_CFG2_SYNC_CLK_SEL_MASK)
#define PPI_CS_CFG2_SYNC_CLK_SEL_GET(x) (((uint32_t)(x) & PPI_CS_CFG2_SYNC_CLK_SEL_MASK) >> PPI_CS_CFG2_SYNC_CLK_SEL_SHIFT)

/*
 * READY_IN_SEL (RW)
 *
 * 0: use two stage sync;
 * 1: use one stage sync
 */
#define PPI_CS_CFG2_READY_IN_SEL_MASK (0x1000U)
#define PPI_CS_CFG2_READY_IN_SEL_SHIFT (12U)
#define PPI_CS_CFG2_READY_IN_SEL_SET(x) (((uint32_t)(x) << PPI_CS_CFG2_READY_IN_SEL_SHIFT) & PPI_CS_CFG2_READY_IN_SEL_MASK)
#define PPI_CS_CFG2_READY_IN_SEL_GET(x) (((uint32_t)(x) & PPI_CS_CFG2_READY_IN_SEL_MASK) >> PPI_CS_CFG2_READY_IN_SEL_SHIFT)

/*
 * INTER_CMD_DLY (RW)
 *
 * set to none-zero value, will add delay between each command sequence for burst cmd,
 * or splited transfer cmd sequence(such as transfer 32bit on 16bit port),
 * CS will be de-assert during the delay.
 */
#define PPI_CS_CFG2_INTER_CMD_DLY_MASK (0xF0U)
#define PPI_CS_CFG2_INTER_CMD_DLY_SHIFT (4U)
#define PPI_CS_CFG2_INTER_CMD_DLY_SET(x) (((uint32_t)(x) << PPI_CS_CFG2_INTER_CMD_DLY_SHIFT) & PPI_CS_CFG2_INTER_CMD_DLY_MASK)
#define PPI_CS_CFG2_INTER_CMD_DLY_GET(x) (((uint32_t)(x) & PPI_CS_CFG2_INTER_CMD_DLY_MASK) >> PPI_CS_CFG2_INTER_CMD_DLY_SHIFT)

/*
 * PORT_SIZE (RW)
 *
 * 00-8bit; 01-16bit; 10-32bit; 11-reserved
 */
#define PPI_CS_CFG2_PORT_SIZE_MASK (0x6U)
#define PPI_CS_CFG2_PORT_SIZE_SHIFT (1U)
#define PPI_CS_CFG2_PORT_SIZE_SET(x) (((uint32_t)(x) << PPI_CS_CFG2_PORT_SIZE_SHIFT) & PPI_CS_CFG2_PORT_SIZE_MASK)
#define PPI_CS_CFG2_PORT_SIZE_GET(x) (((uint32_t)(x) & PPI_CS_CFG2_PORT_SIZE_MASK) >> PPI_CS_CFG2_PORT_SIZE_SHIFT)

/*
 * ENABLE (RW)
 *
 * CS enable
 */
#define PPI_CS_CFG2_ENABLE_MASK (0x1U)
#define PPI_CS_CFG2_ENABLE_SHIFT (0U)
#define PPI_CS_CFG2_ENABLE_SET(x) (((uint32_t)(x) << PPI_CS_CFG2_ENABLE_SHIFT) & PPI_CS_CFG2_ENABLE_MASK)
#define PPI_CS_CFG2_ENABLE_GET(x) (((uint32_t)(x) & PPI_CS_CFG2_ENABLE_MASK) >> PPI_CS_CFG2_ENABLE_SHIFT)

/* Bitfield definition for register of struct array CS: CFG3 */
/*
 * RCMD_END1 (RW)
 *
 * sequential read cmd end index
 */
#define PPI_CS_CFG3_RCMD_END1_MASK (0x3F000000UL)
#define PPI_CS_CFG3_RCMD_END1_SHIFT (24U)
#define PPI_CS_CFG3_RCMD_END1_SET(x) (((uint32_t)(x) << PPI_CS_CFG3_RCMD_END1_SHIFT) & PPI_CS_CFG3_RCMD_END1_MASK)
#define PPI_CS_CFG3_RCMD_END1_GET(x) (((uint32_t)(x) & PPI_CS_CFG3_RCMD_END1_MASK) >> PPI_CS_CFG3_RCMD_END1_SHIFT)

/*
 * RCMD_START1 (RW)
 *
 * sequential read cmd start index
 */
#define PPI_CS_CFG3_RCMD_START1_MASK (0x3F0000UL)
#define PPI_CS_CFG3_RCMD_START1_SHIFT (16U)
#define PPI_CS_CFG3_RCMD_START1_SET(x) (((uint32_t)(x) << PPI_CS_CFG3_RCMD_START1_SHIFT) & PPI_CS_CFG3_RCMD_START1_MASK)
#define PPI_CS_CFG3_RCMD_START1_GET(x) (((uint32_t)(x) & PPI_CS_CFG3_RCMD_START1_MASK) >> PPI_CS_CFG3_RCMD_START1_SHIFT)

/*
 * RCMD_END0 (RW)
 *
 * first read cmd end index
 */
#define PPI_CS_CFG3_RCMD_END0_MASK (0x3F00U)
#define PPI_CS_CFG3_RCMD_END0_SHIFT (8U)
#define PPI_CS_CFG3_RCMD_END0_SET(x) (((uint32_t)(x) << PPI_CS_CFG3_RCMD_END0_SHIFT) & PPI_CS_CFG3_RCMD_END0_MASK)
#define PPI_CS_CFG3_RCMD_END0_GET(x) (((uint32_t)(x) & PPI_CS_CFG3_RCMD_END0_MASK) >> PPI_CS_CFG3_RCMD_END0_SHIFT)

/*
 * RCMD_START0 (RW)
 *
 * first read cmd start index
 */
#define PPI_CS_CFG3_RCMD_START0_MASK (0x3FU)
#define PPI_CS_CFG3_RCMD_START0_SHIFT (0U)
#define PPI_CS_CFG3_RCMD_START0_SET(x) (((uint32_t)(x) << PPI_CS_CFG3_RCMD_START0_SHIFT) & PPI_CS_CFG3_RCMD_START0_MASK)
#define PPI_CS_CFG3_RCMD_START0_GET(x) (((uint32_t)(x) & PPI_CS_CFG3_RCMD_START0_MASK) >> PPI_CS_CFG3_RCMD_START0_SHIFT)

/* Bitfield definition for register of struct array CS: CFG4 */
/*
 * WCMD_END1 (RW)
 *
 * sequential write cmd end index
 */
#define PPI_CS_CFG4_WCMD_END1_MASK (0x3F000000UL)
#define PPI_CS_CFG4_WCMD_END1_SHIFT (24U)
#define PPI_CS_CFG4_WCMD_END1_SET(x) (((uint32_t)(x) << PPI_CS_CFG4_WCMD_END1_SHIFT) & PPI_CS_CFG4_WCMD_END1_MASK)
#define PPI_CS_CFG4_WCMD_END1_GET(x) (((uint32_t)(x) & PPI_CS_CFG4_WCMD_END1_MASK) >> PPI_CS_CFG4_WCMD_END1_SHIFT)

/*
 * WCMD_START1 (RW)
 *
 * sequential write cmd start index
 */
#define PPI_CS_CFG4_WCMD_START1_MASK (0x3F0000UL)
#define PPI_CS_CFG4_WCMD_START1_SHIFT (16U)
#define PPI_CS_CFG4_WCMD_START1_SET(x) (((uint32_t)(x) << PPI_CS_CFG4_WCMD_START1_SHIFT) & PPI_CS_CFG4_WCMD_START1_MASK)
#define PPI_CS_CFG4_WCMD_START1_GET(x) (((uint32_t)(x) & PPI_CS_CFG4_WCMD_START1_MASK) >> PPI_CS_CFG4_WCMD_START1_SHIFT)

/*
 * WCMD_END0 (RW)
 *
 * first write cmd end index
 */
#define PPI_CS_CFG4_WCMD_END0_MASK (0x3F00U)
#define PPI_CS_CFG4_WCMD_END0_SHIFT (8U)
#define PPI_CS_CFG4_WCMD_END0_SET(x) (((uint32_t)(x) << PPI_CS_CFG4_WCMD_END0_SHIFT) & PPI_CS_CFG4_WCMD_END0_MASK)
#define PPI_CS_CFG4_WCMD_END0_GET(x) (((uint32_t)(x) & PPI_CS_CFG4_WCMD_END0_MASK) >> PPI_CS_CFG4_WCMD_END0_SHIFT)

/*
 * WCMD_START0 (RW)
 *
 * first write cmd start index
 */
#define PPI_CS_CFG4_WCMD_START0_MASK (0x3FU)
#define PPI_CS_CFG4_WCMD_START0_SHIFT (0U)
#define PPI_CS_CFG4_WCMD_START0_SET(x) (((uint32_t)(x) << PPI_CS_CFG4_WCMD_START0_SHIFT) & PPI_CS_CFG4_WCMD_START0_MASK)
#define PPI_CS_CFG4_WCMD_START0_GET(x) (((uint32_t)(x) & PPI_CS_CFG4_WCMD_START0_MASK) >> PPI_CS_CFG4_WCMD_START0_SHIFT)

/* Bitfield definition for register of struct array CMD: CMD_CFG */
/*
 * CS_VAL (RW)
 *
 * cs value in current cmd
 */
#define PPI_CMD_CMD_CFG_CS_VAL_MASK (0x20000UL)
#define PPI_CMD_CMD_CFG_CS_VAL_SHIFT (17U)
#define PPI_CMD_CMD_CFG_CS_VAL_SET(x) (((uint32_t)(x) << PPI_CMD_CMD_CFG_CS_VAL_SHIFT) & PPI_CMD_CMD_CFG_CS_VAL_MASK)
#define PPI_CMD_CMD_CFG_CS_VAL_GET(x) (((uint32_t)(x) & PPI_CMD_CMD_CFG_CS_VAL_MASK) >> PPI_CMD_CMD_CFG_CS_VAL_SHIFT)

/*
 * CLK_GATE (RW)
 *
 * the clock gate enable signal, set to output clock signal
 */
#define PPI_CMD_CMD_CFG_CLK_GATE_MASK (0x10000UL)
#define PPI_CMD_CMD_CFG_CLK_GATE_SHIFT (16U)
#define PPI_CMD_CMD_CFG_CLK_GATE_SET(x) (((uint32_t)(x) << PPI_CMD_CMD_CFG_CLK_GATE_SHIFT) & PPI_CMD_CMD_CFG_CLK_GATE_MASK)
#define PPI_CMD_CMD_CFG_CLK_GATE_GET(x) (((uint32_t)(x) & PPI_CMD_CMD_CFG_CLK_GATE_MASK) >> PPI_CMD_CMD_CFG_CLK_GATE_SHIFT)

/*
 * CYCLE_NUM (RW)
 *
 * cmd clock cycles
 */
#define PPI_CMD_CMD_CFG_CYCLE_NUM_MASK (0xFFU)
#define PPI_CMD_CMD_CFG_CYCLE_NUM_SHIFT (0U)
#define PPI_CMD_CMD_CFG_CYCLE_NUM_SET(x) (((uint32_t)(x) << PPI_CMD_CMD_CFG_CYCLE_NUM_SHIFT) & PPI_CMD_CMD_CFG_CYCLE_NUM_MASK)
#define PPI_CMD_CMD_CFG_CYCLE_NUM_GET(x) (((uint32_t)(x) & PPI_CMD_CMD_CFG_CYCLE_NUM_MASK) >> PPI_CMD_CMD_CFG_CYCLE_NUM_SHIFT)

/* Bitfield definition for register of struct array CMD: AD_CFG */
/*
 * DIR3 (RW)
 *
 */
#define PPI_CMD_AD_CFG_DIR3_MASK (0x8000U)
#define PPI_CMD_AD_CFG_DIR3_SHIFT (15U)
#define PPI_CMD_AD_CFG_DIR3_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_DIR3_SHIFT) & PPI_CMD_AD_CFG_DIR3_MASK)
#define PPI_CMD_AD_CFG_DIR3_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_DIR3_MASK) >> PPI_CMD_AD_CFG_DIR3_SHIFT)

/*
 * AD_SEL3 (RW)
 *
 */
#define PPI_CMD_AD_CFG_AD_SEL3_MASK (0x4000U)
#define PPI_CMD_AD_CFG_AD_SEL3_SHIFT (14U)
#define PPI_CMD_AD_CFG_AD_SEL3_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_AD_SEL3_SHIFT) & PPI_CMD_AD_CFG_AD_SEL3_MASK)
#define PPI_CMD_AD_CFG_AD_SEL3_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_AD_SEL3_MASK) >> PPI_CMD_AD_CFG_AD_SEL3_SHIFT)

/*
 * BYTE_SEL3 (RW)
 *
 */
#define PPI_CMD_AD_CFG_BYTE_SEL3_MASK (0x3000U)
#define PPI_CMD_AD_CFG_BYTE_SEL3_SHIFT (12U)
#define PPI_CMD_AD_CFG_BYTE_SEL3_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_BYTE_SEL3_SHIFT) & PPI_CMD_AD_CFG_BYTE_SEL3_MASK)
#define PPI_CMD_AD_CFG_BYTE_SEL3_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_BYTE_SEL3_MASK) >> PPI_CMD_AD_CFG_BYTE_SEL3_SHIFT)

/*
 * DIR2 (RW)
 *
 */
#define PPI_CMD_AD_CFG_DIR2_MASK (0x800U)
#define PPI_CMD_AD_CFG_DIR2_SHIFT (11U)
#define PPI_CMD_AD_CFG_DIR2_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_DIR2_SHIFT) & PPI_CMD_AD_CFG_DIR2_MASK)
#define PPI_CMD_AD_CFG_DIR2_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_DIR2_MASK) >> PPI_CMD_AD_CFG_DIR2_SHIFT)

/*
 * AD_SEL2 (RW)
 *
 */
#define PPI_CMD_AD_CFG_AD_SEL2_MASK (0x400U)
#define PPI_CMD_AD_CFG_AD_SEL2_SHIFT (10U)
#define PPI_CMD_AD_CFG_AD_SEL2_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_AD_SEL2_SHIFT) & PPI_CMD_AD_CFG_AD_SEL2_MASK)
#define PPI_CMD_AD_CFG_AD_SEL2_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_AD_SEL2_MASK) >> PPI_CMD_AD_CFG_AD_SEL2_SHIFT)

/*
 * BYTE_SEL2 (RW)
 *
 */
#define PPI_CMD_AD_CFG_BYTE_SEL2_MASK (0x300U)
#define PPI_CMD_AD_CFG_BYTE_SEL2_SHIFT (8U)
#define PPI_CMD_AD_CFG_BYTE_SEL2_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_BYTE_SEL2_SHIFT) & PPI_CMD_AD_CFG_BYTE_SEL2_MASK)
#define PPI_CMD_AD_CFG_BYTE_SEL2_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_BYTE_SEL2_MASK) >> PPI_CMD_AD_CFG_BYTE_SEL2_SHIFT)

/*
 * DIR1 (RW)
 *
 */
#define PPI_CMD_AD_CFG_DIR1_MASK (0x80U)
#define PPI_CMD_AD_CFG_DIR1_SHIFT (7U)
#define PPI_CMD_AD_CFG_DIR1_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_DIR1_SHIFT) & PPI_CMD_AD_CFG_DIR1_MASK)
#define PPI_CMD_AD_CFG_DIR1_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_DIR1_MASK) >> PPI_CMD_AD_CFG_DIR1_SHIFT)

/*
 * AD_SEL1 (RW)
 *
 */
#define PPI_CMD_AD_CFG_AD_SEL1_MASK (0x40U)
#define PPI_CMD_AD_CFG_AD_SEL1_SHIFT (6U)
#define PPI_CMD_AD_CFG_AD_SEL1_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_AD_SEL1_SHIFT) & PPI_CMD_AD_CFG_AD_SEL1_MASK)
#define PPI_CMD_AD_CFG_AD_SEL1_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_AD_SEL1_MASK) >> PPI_CMD_AD_CFG_AD_SEL1_SHIFT)

/*
 * BYTE_SEL1 (RW)
 *
 */
#define PPI_CMD_AD_CFG_BYTE_SEL1_MASK (0x30U)
#define PPI_CMD_AD_CFG_BYTE_SEL1_SHIFT (4U)
#define PPI_CMD_AD_CFG_BYTE_SEL1_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_BYTE_SEL1_SHIFT) & PPI_CMD_AD_CFG_BYTE_SEL1_MASK)
#define PPI_CMD_AD_CFG_BYTE_SEL1_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_BYTE_SEL1_MASK) >> PPI_CMD_AD_CFG_BYTE_SEL1_SHIFT)

/*
 * DIR0 (RW)
 *
 * 0 for OUT; 1 for IN
 */
#define PPI_CMD_AD_CFG_DIR0_MASK (0x8U)
#define PPI_CMD_AD_CFG_DIR0_SHIFT (3U)
#define PPI_CMD_AD_CFG_DIR0_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_DIR0_SHIFT) & PPI_CMD_AD_CFG_DIR0_MASK)
#define PPI_CMD_AD_CFG_DIR0_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_DIR0_MASK) >> PPI_CMD_AD_CFG_DIR0_SHIFT)

/*
 * AD_SEL0 (RW)
 *
 * 0 for data; 1 for address.
 */
#define PPI_CMD_AD_CFG_AD_SEL0_MASK (0x4U)
#define PPI_CMD_AD_CFG_AD_SEL0_SHIFT (2U)
#define PPI_CMD_AD_CFG_AD_SEL0_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_AD_SEL0_SHIFT) & PPI_CMD_AD_CFG_AD_SEL0_MASK)
#define PPI_CMD_AD_CFG_AD_SEL0_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_AD_SEL0_MASK) >> PPI_CMD_AD_CFG_AD_SEL0_SHIFT)

/*
 * BYTE_SEL0 (RW)
 *
 * select one of the 4 bytes(11 for 31:24,  10 for 23:16, 01 for 15:8, 00 for 7:0)
 */
#define PPI_CMD_AD_CFG_BYTE_SEL0_MASK (0x3U)
#define PPI_CMD_AD_CFG_BYTE_SEL0_SHIFT (0U)
#define PPI_CMD_AD_CFG_BYTE_SEL0_SET(x) (((uint32_t)(x) << PPI_CMD_AD_CFG_BYTE_SEL0_SHIFT) & PPI_CMD_AD_CFG_BYTE_SEL0_MASK)
#define PPI_CMD_AD_CFG_BYTE_SEL0_GET(x) (((uint32_t)(x) & PPI_CMD_AD_CFG_BYTE_SEL0_MASK) >> PPI_CMD_AD_CFG_BYTE_SEL0_SHIFT)

/* Bitfield definition for register of struct array CMD: CTRL_CFG */
/*
 * IO_CFG7 (RW)
 *
 */
#define PPI_CMD_CTRL_CFG_IO_CFG7_MASK (0x10000000UL)
#define PPI_CMD_CTRL_CFG_IO_CFG7_SHIFT (28U)
#define PPI_CMD_CTRL_CFG_IO_CFG7_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG7_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG7_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG7_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG7_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG7_SHIFT)

/*
 * IO_CFG6 (RW)
 *
 */
#define PPI_CMD_CTRL_CFG_IO_CFG6_MASK (0x1000000UL)
#define PPI_CMD_CTRL_CFG_IO_CFG6_SHIFT (24U)
#define PPI_CMD_CTRL_CFG_IO_CFG6_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG6_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG6_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG6_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG6_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG6_SHIFT)

/*
 * IO_CFG5 (RW)
 *
 */
#define PPI_CMD_CTRL_CFG_IO_CFG5_MASK (0x100000UL)
#define PPI_CMD_CTRL_CFG_IO_CFG5_SHIFT (20U)
#define PPI_CMD_CTRL_CFG_IO_CFG5_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG5_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG5_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG5_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG5_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG5_SHIFT)

/*
 * IO_CFG4 (RW)
 *
 */
#define PPI_CMD_CTRL_CFG_IO_CFG4_MASK (0x10000UL)
#define PPI_CMD_CTRL_CFG_IO_CFG4_SHIFT (16U)
#define PPI_CMD_CTRL_CFG_IO_CFG4_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG4_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG4_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG4_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG4_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG4_SHIFT)

/*
 * IO_CFG3 (RW)
 *
 */
#define PPI_CMD_CTRL_CFG_IO_CFG3_MASK (0x1000U)
#define PPI_CMD_CTRL_CFG_IO_CFG3_SHIFT (12U)
#define PPI_CMD_CTRL_CFG_IO_CFG3_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG3_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG3_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG3_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG3_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG3_SHIFT)

/*
 * IO_CFG2 (RW)
 *
 */
#define PPI_CMD_CTRL_CFG_IO_CFG2_MASK (0x100U)
#define PPI_CMD_CTRL_CFG_IO_CFG2_SHIFT (8U)
#define PPI_CMD_CTRL_CFG_IO_CFG2_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG2_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG2_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG2_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG2_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG2_SHIFT)

/*
 * IO_CFG1 (RW)
 *
 */
#define PPI_CMD_CTRL_CFG_IO_CFG1_MASK (0x10U)
#define PPI_CMD_CTRL_CFG_IO_CFG1_SHIFT (4U)
#define PPI_CMD_CTRL_CFG_IO_CFG1_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG1_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG1_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG1_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG1_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG1_SHIFT)

/*
 * IO_CFG0 (RW)
 *
 * for OUT, it defines the output value(0 or 1);
 * for IN, it defines whether to wait for ready(ready polarity is defined in ctrl_pad_pol)
 */
#define PPI_CMD_CTRL_CFG_IO_CFG0_MASK (0x1U)
#define PPI_CMD_CTRL_CFG_IO_CFG0_SHIFT (0U)
#define PPI_CMD_CTRL_CFG_IO_CFG0_SET(x) (((uint32_t)(x) << PPI_CMD_CTRL_CFG_IO_CFG0_SHIFT) & PPI_CMD_CTRL_CFG_IO_CFG0_MASK)
#define PPI_CMD_CTRL_CFG_IO_CFG0_GET(x) (((uint32_t)(x) & PPI_CMD_CTRL_CFG_IO_CFG0_MASK) >> PPI_CMD_CTRL_CFG_IO_CFG0_SHIFT)



/* CS register group index macro definition */
#define PPI_CS_0 (0UL)
#define PPI_CS_1 (1UL)
#define PPI_CS_2 (2UL)
#define PPI_CS_3 (3UL)

/* CMD register group index macro definition */
#define PPI_CMD_0 (0UL)
#define PPI_CMD_1 (1UL)
#define PPI_CMD_2 (2UL)
#define PPI_CMD_3 (3UL)
#define PPI_CMD_4 (4UL)
#define PPI_CMD_5 (5UL)
#define PPI_CMD_6 (6UL)
#define PPI_CMD_7 (7UL)
#define PPI_CMD_8 (8UL)
#define PPI_CMD_9 (9UL)
#define PPI_CMD_10 (10UL)
#define PPI_CMD_11 (11UL)
#define PPI_CMD_12 (12UL)
#define PPI_CMD_13 (13UL)
#define PPI_CMD_14 (14UL)
#define PPI_CMD_15 (15UL)
#define PPI_CMD_16 (16UL)
#define PPI_CMD_17 (17UL)
#define PPI_CMD_18 (18UL)
#define PPI_CMD_19 (19UL)
#define PPI_CMD_20 (20UL)
#define PPI_CMD_21 (21UL)
#define PPI_CMD_22 (22UL)
#define PPI_CMD_23 (23UL)
#define PPI_CMD_24 (24UL)
#define PPI_CMD_25 (25UL)
#define PPI_CMD_26 (26UL)
#define PPI_CMD_27 (27UL)
#define PPI_CMD_28 (28UL)
#define PPI_CMD_29 (29UL)
#define PPI_CMD_30 (30UL)
#define PPI_CMD_31 (31UL)
#define PPI_CMD_32 (32UL)
#define PPI_CMD_33 (33UL)
#define PPI_CMD_34 (34UL)
#define PPI_CMD_35 (35UL)
#define PPI_CMD_36 (36UL)
#define PPI_CMD_37 (37UL)
#define PPI_CMD_38 (38UL)
#define PPI_CMD_39 (39UL)
#define PPI_CMD_40 (40UL)
#define PPI_CMD_41 (41UL)
#define PPI_CMD_42 (42UL)
#define PPI_CMD_43 (43UL)
#define PPI_CMD_44 (44UL)
#define PPI_CMD_45 (45UL)
#define PPI_CMD_46 (46UL)
#define PPI_CMD_47 (47UL)
#define PPI_CMD_48 (48UL)
#define PPI_CMD_49 (49UL)
#define PPI_CMD_50 (50UL)
#define PPI_CMD_51 (51UL)
#define PPI_CMD_52 (52UL)
#define PPI_CMD_53 (53UL)
#define PPI_CMD_54 (54UL)
#define PPI_CMD_55 (55UL)
#define PPI_CMD_56 (56UL)
#define PPI_CMD_57 (57UL)
#define PPI_CMD_58 (58UL)
#define PPI_CMD_59 (59UL)
#define PPI_CMD_61 (61UL)
#define PPI_CMD_62 (62UL)
#define PPI_CMD_63 (63UL)


#endif /* HPM_PPI_H */
