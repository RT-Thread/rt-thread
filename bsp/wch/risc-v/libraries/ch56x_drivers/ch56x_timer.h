/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#ifndef __CH56X_TIMER_H__
#define __CH56X_TIMER_H__

#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

union _timer_ctrl_mod
{
    uint8_t reg;
    struct
    {
        uint8_t mode_in     : 1;  // B.0 : RW, timer mode setting
        uint8_t all_clear   : 1;  // B.1 : RW, clear FIFO/count/int-flag
        uint8_t count_en    : 1;  // B.2 : RW, enable timer module
        uint8_t out_en      : 1;  // B.3 : RW, timer output enable
        uint8_t out_polar   : 1;  // B.4 : RW, output polarity for PWM mode
        uint8_t resv_5      : 1;
        uint8_t pwm_repeat  : 2;  // B.7-6 : RW, PWM repeat count, 1/4/8/16
    };
    struct
    {
        uint8_t stuff_0     : 6;
        uint8_t cap_edge    : 2;  // B.7-6 : RW, capture edge mode
    };
};
#define RB_TMR_MODE_IN      0x01
#define RB_TMR_ALL_CLEAR    0x02
#define RB_TMR_COUNT_EN     0x04
#define RB_TMR_OUT_EN       0x08
#define RB_TMR_OUT_POLAR    0x10
#define RB_TMR_CAP_COUNT    0x10
#define RB_TMR_PWM_REPEAT   0xc0
#define RB_TMR_CAP_EDGE     0xc0

#define TMR_MODE_TIMER_PWM  0
#define TMR_MODE_CAP_COUNT  1
#define TMR_PWM_REPEAT_1    0
#define TMR_PWM_REPEAT_4    1
#define TMR_PWM_REPEAT_8    2
#define TMR_PWM_REPEAT_16   3
#define TMR_CAP_EDGE_NONE   0
#define TMR_CAP_EDGE_BOTH   1
#define TMR_CAP_EDGE_F2F    2
#define TMR_CAP_EDGE_R2R    3

union _timer_ctrl_dma
{
    uint8_t reg;
    struct
    {
        uint8_t dma_enable  : 1;  // B.0 : RW, enable DMA
        uint8_t resv_1      : 1;
        uint8_t dma_loop    : 1;  // B.2 : RW, enable DMA address looping
        uint8_t resv_3      : 5;
    };
};
#define RB_TMR_DMA_ENABLE   0x01
#define RB_TMR_DMA_LOOP     0x04

union _timer_interrupt
{
    uint8_t reg;
    struct
    {
        uint8_t cyc_end     : 1;  // B.0
        uint8_t data_act    : 1;  // B.1
        uint8_t fifo_hf     : 1;  // B.2
        uint8_t dma_end     : 1;  // B.3
        uint8_t fifo_ov     : 1;  // B.4
        uint8_t resv_5      : 3;
    };
};
#define RB_TMR_IX_MASK      0x1f
#define RB_TMR_IE_CYC_END   0x01  // RW, enable interrupt for timer capture count timeout or PWM cycle end
#define RB_TMR_IE_DATA_ACT  0x02  // RW, enable interrupt for timer capture input action or PWM trigger
#define RB_TMR_IE_FIFO_HF   0x04  // RW, enable interrupt for timer FIFO half (capture fifo >=4 or PWM fifo <=3)
#define RB_TMR_IE_DMA_END   0x08  // RW, enable interrupt for timer1/2 DMA completion
#define RB_TMR_IE_FIFO_OV   0x10  // RW, enable interrupt for timer FIFO overflow

#define RB_TMR_IF_CYC_END   0x01  // RW1, interrupt flag for timer capture count timeout or PWM cycle end
#define RB_TMR_IF_DATA_ACT  0x02  // RW1, interrupt flag for timer capture input action or PWM trigger
#define RB_TMR_IF_FIFO_HF   0x04  // RW1, interrupt flag for timer FIFO half (capture fifo >=4 or PWM fifo <=3)
#define RB_TMR_IF_DMA_END   0x08  // RW1, interrupt flag for timer1/2 DMA completion
#define RB_TMR_IF_FIFO_OV   0x10  // RW1, interrupt flag for timer FIFO overflow

/*
 * 0x00  R8_TMRx_CTRL_MOD:   mode setting register
 * 0x01  R8_TMRx_CTRL_DMA:   DMA control register
 * 0x02  R8_TMRx_INTER_EN:   interrupt enable register
 * 0x06  R8_TMRx_INT_FLAG:   interrupt flag register
 * 0x07  R8_TMRx_FIFO_COUNT: RO, FIFO count register
 * 0x08  R32_TMRx_COUNT:     RO, timer current count register
 * 0x0c  R32_TMRx_CNT_END:   RW, timer count end register
 * 0x10  R32_TMRx_FIFO:      RO/WO, FIFO data register, LSB 26 bits
 * 0x14  R32_TMRx_DMA_NOW:   RW, DMA buffer current address, LSB 18 bits
 * 0x18  R32_TMRx_DMA_BEG:   RW, DMA buffer begin address, LSB 18 bits
 * 0x1c  R32_TMRx_DMA_END:   RW, DMA buffer end address (exclusive), LSB 18 bits
 *
 * Note: DMA related registers (0x10,0x14,0x18,0x1c) are TMR1/2 only
 *
 * CAVEAT: gcc (as of 8.2.0) tends to read 32-bit word for bit field test.
 * Be careful for those with side effect for read.
 */
struct timer_registers
{
    union _timer_ctrl_mod   CTRL_MOD;
    union _timer_ctrl_dma   CTRL_DMA;
    union _timer_interrupt  INTER_EN;
    uint8_t                 resv_3[3];
    union _timer_interrupt  INT_FLAG;
    uint8_t                 FIFO_COUNT;
    uint32_t                COUNT;
    uint32_t                CNT_END;
    uint32_t                FIFO;
    uint32_t                DMA_NOW;
    uint32_t                DMA_BEG;
    uint32_t                DMA_END;
} __packed;

CHECK_STRUCT_SIZE(struct timer_registers, 0x20);

#ifdef __cplusplus
}
#endif

#endif
