/*
 * ===========================================================================================
 *
 *       Filename:  sunxi_hal_spi.h
 *
 *    Description:  SPI HAL definition.
 *
 *        Version:  Melis3.0
 *         Create:  2020-04-08 11:11:56
 *       Revision:  none
 *       Compiler:  GCC:version 9.2.1
 *
 *         Author:  bantao@allwinnertech.com
 *   Organization:  SWC-BPD
 *  Last Modified:  2020-04-08 16:02:11
 *
 * ===========================================================================================
 */

#ifndef SUNXI_IR_RX_H
#define SUNXI_IR_RX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "sunxi_hal_common.h"
#include <hal_gpio.h>
#include <hal_sem.h>
#include <hal_clk.h>


#define SUNXI_IRADC_PBASE         0X07040000 /* 0x34 */

#define SUNXI_IRQ_IRADC                 155

#define IRADC_PIN    GPIO_PH0
#define IR_MUXSEL 4
#define IR_DRVSEL 2


/* Registers */
#define IR_CTRL_REG     (0x00)  /* IR Control */
#define IR_RXCFG_REG        (0x10)  /* Rx Config */
#define IR_RXDAT_REG        (0x20)  /* Rx Data */
#define IR_RXINTE_REG       (0x2C)  /* Rx Interrupt Enable */
#define IR_RXINTS_REG       (0x30)  /* Rx Interrupt Status */
#define IR_SPLCFG_REG       (0x34)  /* IR Sample Config */

#define IR_FIFO_SIZE        (64)    /* 64Bytes */

#define IR_SIMPLE_UNIT      (21000)     /* simple in ns */
#define IR_CLK          (24000000)  /* 24Mhz */
#define IR_SAMPLE_DEV       (0x3<<0)    /* 24MHz/512 =46875Hz (~21us) */

/* Active Threshold (0+1)*128clock*21us = 2.6ms */
#define IR_ACTIVE_T     ((0&0xff)<<16)

/* Filter Threshold = 16*21us = 336us < 500us */
#define IR_RXFILT_VAL       (((16)&0x3f)<<2)

/* Filter Threshold = 22*21us = 336us < 500us */
#define IR_RXFILT_VAL_RC5   (((22)&0x3f)<<2)

/* Idle Threshold = (5+1)*128clock*21us = 16ms > 9ms */
#define IR_RXIDLE_VAL       (((5)&0xff)<<8)

/* Active Threshold (0+1)*128clock*21us = 2.6ms */
#define IR_ACTIVE_T_SAMPLE  ((16&0xff)<<16)

#define IR_ACTIVE_T_C       (1<<23)     /* Active Threshold */
#define IR_CIR_MODE     (0x3<<4)    /* CIR mode enable */
#define IR_ENTIRE_ENABLE    (0x3<<0)    /* IR entire enable */
#define IR_FIFO_20      (((20)-1)<<8)
#define IR_IRQ_STATUS       ((0x1<<4)|0x3)
#define IR_BOTH_PULSE       (0x1 << 6)
#define IR_LOW_PULSE        (0x2 << 6)
#define IR_HIGH_PULSE       (0x3 << 6)

/*Bit Definition of IR_RXINTS_REG Register*/
#define IR_RXINTS_RXOF      (0x1<<0)    /* Rx FIFO Overflow */
#define IR_RXINTS_RXPE      (0x1<<1)    /* Rx Packet End */
#define IR_RXINTS_RXDA      (0x1<<4)    /* Rx FIFO Data Available */


enum ir_mode {
    CIR_MODE_ENABLE,
    IR_MODULE_ENABLE,
    IR_BOTH_PULSE_MODE, /* new feature to avoid noisy */
    IR_LOW_PULSE_MODE,
    IR_HIGH_PULSE_MODE,
};

enum ir_sample_config {
    IR_SAMPLE_REG_CLEAR,
    IR_CLK_SAMPLE,
    IR_FILTER_TH_NEC,
    IR_FILTER_TH_RC5,
    IR_IDLE_TH,
    IR_ACTIVE_TH,
    IR_ACTIVE_TH_SAMPLE,
};

enum ir_irq_config {
    IR_IRQ_STATUS_CLEAR,
    IR_IRQ_ENABLE,
    IR_IRQ_FIFO_SIZE,
};

typedef enum
{
    IR_PIN_ERR = -3,
    IR_CLK_ERR = -2,
    IR_IRQ_ERR = -1,
    IR_OK = 0,
} hal_ir_status_t;

typedef int (*ir_callback_t)(uint32_t data_type, uint32_t data);

typedef struct sunxi_ir
{
    uint16_t irq_num;
    uint32_t reg_base;

    gpio_pin_t pin;
    uint8_t pin_mux;
    uint8_t pin_drv;

    ir_callback_t callback;
} hal_ir_t;

int hal_ir_register_callback(ir_callback_t callback);
int hal_ir_init(void);

#ifdef __cplusplus
}
#endif


#endif
