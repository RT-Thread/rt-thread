#ifndef __BFLB_PEC_IP_H__
#define __BFLB_PEC_IP_H__

#include "bflb_core.h"

#define PEC0                    0
#define PEC_MAX                 1

#define PEC_SM0                 0
#define PEC_SM1                 1
#define PEC_SM2                 2
#define PEC_SM3                 3
#define PEC_SM_MAX              4

#define PEC_FLAG_0              (1 << 0)
#define PEC_FLAG_1              (1 << 1)
#define PEC_FLAG_2              (1 << 2)
#define PEC_FLAG_3              (1 << 3)
#define PEC_FLAG_4              (1 << 4)
#define PEC_FLAG_5              (1 << 5)
#define PEC_FLAG_6              (1 << 6)
#define PEC_FLAG_7              (1 << 7)

#define PEC_IP_NULL             0
#define PEC_IP_PWM              1
#define PEC_IP_UART_TX          2
#define PEC_IP_UART_RX          3
#define PEC_IP_SPI              4
#define PEC_IP_I2C              5
#define PEC_IP_WS2812           6
#define PEC_IP_JTAG             7
#define PEC_IP_DPI              8
#define PEC_IP_LA               9
#define PEC_IP_SEG              10
#define PEC_IP_DBI_B            11
#define PEC_IP_4xI2S            12

#define PEC_ERR_OK              0
#define PEC_ERR_NOT_SUPPORT     1
#define PEC_ERR_PIN_CONFLICT    2
#define PEC_ERR_SM_LACK         3
#define PEC_ERR_CODE_SPACE_LACK 4
#define PEC_ERR_FLAG_LACK       5

extern uint32_t bflb_pec_get_tx_fifo_addr(uint8_t pec_id, uint8_t sm_id);
extern uint32_t bflb_pec_get_rx_fifo_addr(uint8_t pec_id, uint8_t sm_id);
extern void bflb_pec_dma_tx_enable(uint8_t pec_id, uint8_t sm_id, uint8_t enable);
extern void bflb_pec_dma_rx_enable(uint8_t pec_id, uint8_t sm_id, uint8_t enable);

struct bflb_pec_pwm_s {
    uint32_t high_cnt; /*!< high level count */
    uint32_t low_cnt;  /*!< low level count */
    uint16_t div;      /*!< divisor */
    uint8_t pin;       /*!< PWM output assert pin index */
    uint8_t pec;
    uint8_t sm;
    uint8_t addr;
};

int bflb_pec_pwm_init(struct bflb_pec_pwm_s *pwm);
void bflb_pec_pwm_start(struct bflb_pec_pwm_s *pwm);
void bflb_pec_pwm_stop(struct bflb_pec_pwm_s *pwm);

struct bflb_pec_jtag_s {
    uint8_t pin_tck;
    uint8_t pin_tms;
    uint8_t pin_tdo;
    uint8_t pin_tdi;
    uint8_t pec;
    uint8_t sm;
    uint8_t addr;
};

int bflb_pec_jtag_init(struct bflb_pec_jtag_s *jtag);
void bflb_pec_jtag_set_tck(struct bflb_pec_jtag_s *jtag, uint8_t value);
void bflb_pec_jtag_set_tms(struct bflb_pec_jtag_s *jtag, uint8_t value);
void bflb_pec_jtag_set_tdi(struct bflb_pec_jtag_s *jtag, uint8_t value);
int bflb_pec_jtag_get_tdo(struct bflb_pec_jtag_s *jtag);
void bflb_pec_jtag_set_path(struct bflb_pec_jtag_s *jtag, uint32_t path, uint32_t bits);
void bflb_pec_jtag_select_ir(struct bflb_pec_jtag_s *jtag);
void bflb_pec_jtag_exit_ir(struct bflb_pec_jtag_s *jtag);
void bflb_pec_jtag_select_dr(struct bflb_pec_jtag_s *jtag);
void bflb_pec_jtag_exit_dr(struct bflb_pec_jtag_s *jtag);
void bflb_pec_jtag_scan_ir(struct bflb_pec_jtag_s *jtag, uint8_t ir_bits, uint8_t *ir_out, uint8_t *ir_in);
void bflb_pec_jtag_scan_dr(struct bflb_pec_jtag_s *jtag, uint8_t dr_bits, uint8_t *dr_out, uint8_t *dr_in);
void bflb_pec_jtag_scan(struct bflb_pec_jtag_s *jtag, uint8_t ir_bits, uint8_t *ir_out, uint8_t *ir_in, uint8_t dr_bits, uint8_t *dr_out, uint8_t *dr_in);
void bflb_pec_jtag_write_ir(struct bflb_pec_jtag_s *jtag, uint8_t ir_bits, uint8_t *ir_out);
void bflb_pec_jtag_write_dr(struct bflb_pec_jtag_s *jtag, uint8_t dr_bits, uint8_t *dr_out);
void bflb_pec_jtag_read_dr(struct bflb_pec_jtag_s *jtag, uint8_t dr_bits, uint8_t *dr_in);

/* pixel format */
#define PEC_DBI_B_PIXEL_FORMAT_NRGB8888 1 /* 32-bit */
#define PEC_DBI_B_PIXEL_FORMAT_NBGR8888 2 /* 32-bit */
#define PEC_DBI_B_PIXEL_FORMAT_RGB888   3 /* 24-bit */
#define PEC_DBI_B_PIXEL_FORMAT_BGR888   4 /* 24-bit */
#define PEC_DBI_B_PIXEL_FORMAT_RGB565   5 /* 16-bit */
#define PEC_DBI_B_PIXEL_FORMAT_BGR565   6 /* 16-bit */

/* transmit mode */
#define PEC_DBI_TRANSMIT_MODE_CMD       0
#define PEC_DBI_TRANSMIT_MODE_PIXEL     1

struct bflb_pec_dbi_b_s {
    uint32_t clk_src;
    uint32_t clk;
    uint8_t pixel_format;
    uint8_t pin_dc;
    uint8_t pin_wr;
    uint8_t pin_data;
    uint8_t pec;
    uint8_t sm;
    uint8_t addr;
    uint8_t fifo_threshold;
};

int bflb_pec_dbi_b_init(struct bflb_pec_dbi_b_s *dbi_b);
uint32_t bflb_pec_dbi_b_build_head(struct bflb_pec_dbi_b_s *dbi_b, uint8_t transmit_mode, uint8_t cmd, size_t data_num);
uint32_t bflb_pec_dbi_b_get_fifo_address(struct bflb_pec_dbi_b_s *dbi_b);
int bflb_pec_dbi_b_get_fifo_cnt(struct bflb_pec_dbi_b_s *dbi_b);
int bflb_pec_dbi_b_dma_enable(struct bflb_pec_dbi_b_s *dbi_b, bool en);

/* Signal polarity selection */
#define V_SYNC_SINGLE_POL 0
#define H_SYNC_SINGLE_POL 0
#define DE_SINGLE_POL     1

struct bflb_pec_dpi_s {
    uint16_t width;
    uint16_t height;

    uint16_t hsw;
    uint16_t hbp;
    uint16_t hfp;

    uint16_t vsw;
    uint16_t vbp;
    uint16_t vfp;

    bool data_latch_mode;
    bool de_sig_enable;
    bool de_sig_polarity;
    bool v_sync_sig_polarity;
    bool h_sync_sig_polarity;

    uint32_t *invalid_row_para;

    uint16_t frame_rate;
    uint16_t data_format;

    uint8_t pin_clk;
    uint8_t pin_hs;
    uint8_t pin_data;
    uint8_t pec;
    uint8_t sm;
};

int bflb_pec_dpi_init(struct bflb_pec_dpi_s *dpi);

#define PEC_I2S_SAMPLE_RATE_24KHZ      1
#define PEC_I2S_SAMPLE_RATE_48KHZ      2
#define PEC_I2S_SAMPLE_RATE_96KHZ      3

#define PEC_I2S_DATA_FORMAT_BIT24IN32R 0
#define PEC_I2S_DATA_FORMAT_BIT16      1
#define PEC_I2S_DATA_FORMAT_BIT32      2

struct bflb_pec_i2sx4_s {
    uint8_t sample_rate;
    uint8_t data_format;
    uint8_t pin_bck;
    uint8_t pin_ws;
    uint8_t pin_d0;
    uint8_t pin_d1;
    uint8_t pin_d2;
    uint8_t pin_d3;
    uint8_t pec;
    // uint8_t sm;
    // uint8_t addr;
    uint8_t flag;
};

int bflb_pec_i2sx4_init(struct bflb_pec_i2sx4_s *i2s);
void bflb_pec_i2sx4_enable(struct bflb_pec_i2sx4_s *i2s);
void bflb_pec_i2sx4_disable(struct bflb_pec_i2sx4_s *i2s);
void bflb_pec_i2sx4_rx_start(struct bflb_pec_i2sx4_s *i2s);
void bflb_pec_i2sx4_rx_stop(struct bflb_pec_i2sx4_s *i2s);
uint8_t bflb_pec_i2sx4_get_data(struct bflb_pec_i2sx4_s *i2s, uint8_t ch, uint32_t *data);

#endif /* __BFLB_PEC_IP_H__ */
