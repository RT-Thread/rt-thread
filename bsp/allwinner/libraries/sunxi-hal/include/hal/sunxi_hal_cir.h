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

#ifndef _CIR_H_
#define _CIR_H_

#include "hal_clk.h"
#include "hal_reset.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Registers */
#define CIR_CTRL        (0x00)  /* IR Control */
#define CIR_RXCTRL      (0x10)  /* Rx Config */
#define CIR_RXFIFO      (0x20)  /* Rx Data */
#define CIR_RXINT       (0x2C)  /* Rx Interrupt Enable */
#define CIR_RXSTA       (0x30)  /* Rx Interrupt Status */
#define CIR_CONFIG      (0x34)  /* IR Sample Config */

/*CIR_CTRL*/
#define GEN_OFFSET      0
#define RXEN_OFFSET     1
#define CIR_ENABLE_OFFSET   4
#define CIR_MODE_OFFSET     6
/*global enable*/
#define GEN         (0x01 << GEN_OFFSET)
/*receiver block enable*/
#define RXEN            (0x01 << RXEN_OFFSET)
/*cir enable*/
#define CIR_ENABLE      (0x03 << CIR_ENABLE_OFFSET)
/*active pulse accept mode*/
#define CIR_MODE        (0x03 << CIR_MODE_OFFSET)

/*CIR_RXCTRL*/
#define RPPI_OFFSET     2
#define RPPI            (0x01 << RPPI_OFFSET)   /*receiver pulse polarity invert*/

/*CIR_RXINT*/
#define ROI_EN_OFFSET       0
#define PREI_EN_OFFSET      1
#define RAI_EN_OFFSET       4
#define DRQ_EN_OFFSET       5
#define RAL_OFFSET      8
/*receiver fifo overrun interrupt enable*/
#define ROI_EN          (0x01 << ROI_EN_OFFSET)
/*receiver packet end interrupt enable*/
#define PREI_EN         (0x01 << PREI_EN_OFFSET)
/*rx fifo available interrupt enable*/
#define RAI_EN          (0x01 << RAI_EN_OFFSET)
/*rx fifo dma enable*/
#define DRQ_EN          (0x01 << DRQ_EN_OFFSET)
/*rx fifo available received byte level*/
#define RAL         (0x3f << RAL_OFFSET)
#define IRQ_MASK        (0x3f)

/*CIR_RXSTA*/
#define ROI_OFFSET      0
#define RPE_OFFSET      1
#define RA_OFFSET       4
#define STAT_OFFSET     7
#define RAC_OFFSET      8
#define ROI         (0x01 << ROI_OFFSET)    /*receiver fifo overrun*/
#define RPE         (0x01 << RPE_OFFSET)    /*receiver packet end reg*/
#define RA          (0x01 << RA_OFFSET) /*rx fifo available*/
#define STAT            (0x01 << STAT_OFFSET)   /*status of cir, 0:idle, 1:busy*/
#define RAC         (0x7f << RAC_OFFSET)    /*rx fifo available counter*/

/*CIR_CONFIG*/
#define SCS_OFFSET      0
#define NTHR_OFFSET     2
#define ITHR_OFFSET     8
#define ATHR_OFFSET     16
#define ATHC_OFFSET     23
#define SCS2_OFFSET     24
#define SCS         (0x03 << SCS_OFFSET)    /*sample clk select for cir*/
#define NTHR            (0x3f << NTHR_OFFSET)   /*noise threshold for cir*/
#define ITHR            (0xff << ITHR_OFFSET)   /*idle threshold for cir*/
#define ATHR            (0x7f << ATHR_OFFSET)   /*active threshold for cir*/
#define ATHC            (0x01 << ATHC_OFFSET)   /*active threshold control for cir*/
#define SCS2            (0x01 << SCS2_OFFSET)   /*bit2 of sample clock select for cir*/

#define CIR_NOISE_THR_NEC   32
#define CIR_NOISE_THR_RC5   22

typedef enum {
   CIR_MASTER_0 = 0,
   CIR_MASTER_NUM,
} cir_port_t;

typedef enum {
   CIR_BOTH_PULSE = 0x01,   /*both positive and negative pulses*/
   CIR_LOW_PULSE  = 0x02,   /*only negative pulse*/
   CIR_HIGH_PULSE = 0x03,   /*only positive pulse*/
} cir_mode_t;

typedef enum {
   CIR_PIN_ERR = -4,
   CIR_CLK_ERR = -3,
   CIR_IRQ_ERR = -2,
   CIR_PORT_ERR = -1,
   CIR_OK = 0,
} cir_status_t;

typedef enum {
   CIR_CLK_DIV64 = 0x0,
   CIR_CLK_DIV128 = 0x01,
   CIR_CLK_DIV256 = 0x02,
   CIR_CLK_DIV512 = 0x03,
   CIR_CLK = 0x04,
} cir_sample_clock_t;

typedef struct {
    uint32_t gpio;
    uint8_t enable_mux;
    uint8_t disable_mux;
} cir_gpio_t;

typedef struct {
    uint32_t bus_clk;
    uint32_t mclk;
    uint32_t pclk;
} cir_clk_t;

typedef int (*cir_callback_t)(cir_port_t port, uint32_t data_type, uint32_t data);

typedef struct {
    cir_port_t port;
    unsigned long base;
    uint32_t irq;
    cir_clk_t *clk;
    cir_gpio_t *pin;
    cir_callback_t callback;
    uint8_t status;

    hal_clk_t bclk;
    hal_clk_t pclk;
    hal_clk_t mclk;
    hal_clk_t test_clk;

    hal_clk_id_t m_clk_id;
    hal_clk_id_t p_clk_id;
    hal_clk_id_t b_clk_id;
    hal_clk_id_t test_clk_id;

    hal_clk_type_t cir_clk_type_R;
    hal_clk_type_t cir_clk_type_FIXED;
    hal_clk_type_t test_clk_type;

    struct reset_control *cir_reset;
} sunxi_cir_t;

void sunxi_cir_callback_register(cir_port_t port, cir_callback_t callback);
void sunxi_cir_mode_enable(cir_port_t port, uint8_t enable);
void sunxi_cir_mode_config(cir_port_t port, cir_mode_t mode);
void sunxi_cir_sample_clock_select(cir_port_t port, cir_sample_clock_t div);
void sunxi_cir_sample_noise_threshold(cir_port_t port, int8_t threshold);
void sunxi_cir_sample_idle_threshold(cir_port_t port, int8_t threshold);
void sunxi_cir_sample_active_threshold(cir_port_t port, int8_t threshold);
void sunxi_cir_sample_active_thrctrl(cir_port_t port, int8_t enable);
void sunxi_cir_fifo_level(cir_port_t port, int8_t size);
void sunxi_cir_irq_enable(cir_port_t port, int enable);
void sunxi_cir_irq_disable(cir_port_t port);
void sunxi_cir_signal_invert(cir_port_t port, uint8_t invert);
void sunxi_cir_module_enable(cir_port_t port, int8_t enable);
cir_status_t sunxi_cir_init(cir_port_t port);
void sunxi_cir_deinit(cir_port_t port);
#ifdef CONFIG_STANDBY
void sunxi_cir_suspend(cir_port_t port);
void sunxi_cir_resume(cir_port_t port);
#endif

#ifdef __cplusplus
}
#endif

#endif
