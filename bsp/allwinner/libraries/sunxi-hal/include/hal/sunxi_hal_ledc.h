#ifndef __HAL_LEDC_H
#define __HAL_LEDC_H

#include "sunxi_hal_common.h"
#include "ledc/platform_ledc.h"
#include "ledc/common_ledc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SUNXI_LEDC_FIFO_DEPTH 32

enum ledc_output_mode_val {
    LEDC_OUTPUT_GRB = 0 << 6,
    LEDC_OUTPUT_GBR = 1 << 6,
    LEDC_OUTPUT_RGB = 2 << 6,
    LEDC_OUTPUT_RBG = 3 << 6,
    LEDC_OUTPUT_BGR = 4 << 6,
    LEDC_OUTPUT_BRG = 5 << 6
};

enum {
    DEBUG_INIT    = 1U << 0,
    DEBUG_SUSPEND = 1U << 1,
    DEBUG_INFO    = 1U << 2,
    DEBUG_INFO1   = 1U << 3,
    DEBUG_INFO2   = 1U << 4,
};

struct ledc_config {
    unsigned int led_count;
    unsigned int reset_ns;
    unsigned int t1h_ns;
    unsigned int t1l_ns;
    unsigned int t0h_ns;
    unsigned int t0l_ns;
    unsigned int wait_time0_ns;
    unsigned long long wait_time1_ns;
    unsigned int wait_data_time_ns;
    char *output_mode;
    unsigned int *data;
    unsigned int length;
};

enum ledc_irq_ctrl_reg {
    LEDC_TRANS_FINISH_INT_EN     = (1 << 0),
    LEDC_FIFO_CPUREQ_INT_EN      = (1 << 1),
    LEDC_WAITDATA_TIMEOUT_INT_EN = (1 << 3),
    LEDC_FIFO_OVERFLOW_INT_EN    = (1 << 4),
    LEDC_GLOBAL_INT_EN           = (1 << 5),
};

enum ledc_irq_status_reg {
    LEDC_TRANS_FINISH_INT     = (1 << 0),
    LEDC_FIFO_CPUREQ_INT      = (1 << 1),
    LEDC_WAITDATA_TIMEOUT_INT = (1 << 3),
    LEDC_FIFO_OVERFLOW_INT    = (1 << 4),
    LEDC_FIFO_FULL            = (1 << 16),
    LEDC_FIFO_EMPTY           = (1 << 17),
};


void hal_ledc_init(void);
void hal_ledc_deinit(void);
void hal_ledc_trans_data(struct ledc_config *ledc);
void hal_ledc_clear_all_irq(void);
unsigned int hal_ledc_get_irq_status(void);
void hal_ledc_dma_callback(void *para);
void hal_ledc_reset(void);

#ifdef __cplusplus
}
#endif

#endif
