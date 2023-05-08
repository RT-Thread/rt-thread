#include "bflb_ir.h"
#include "bflb_clock.h"
#include "hardware/ir_reg.h"

#define DIVIDE_ROUND(a, b) ((2 * a + b) / (2 * b))

#if !defined(BL616)
void bflb_ir_tx_init(struct bflb_device_s *dev, const struct bflb_ir_tx_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t ir_clock;
    struct bflb_ir_tx_config_s *tx_config = (struct bflb_ir_tx_config_s *)config;

#if defined(BL602) || defined(BL702)
    *(uint32_t *)0x40000224 |= 1 << 31;
#else
    *(uint32_t *)0x20000144 |= 1 << 31;
#endif

    if (bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_IR, 0)) {
        ir_clock = bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_IR, 0);
    } else {
        ir_clock = 2000000;
    }

    if (tx_config->tx_mode == IR_TX_NEC) {
        tx_config->data_bits = 32;
        tx_config->tail_inverse = 0;
        tx_config->tail_enable = 1;
        tx_config->head_inverse = 0;
        tx_config->head_enable = 1;
        tx_config->logic1_inverse = 0;
        tx_config->logic0_inverse = 0;
        tx_config->data_enable = 1;
        tx_config->swm_enable = 0;
        tx_config->output_modulation = 1;
        tx_config->output_inverse = 0;
        tx_config->freerun_enable = 0;
        tx_config->continue_enable = 0;
        tx_config->fifo_width = IR_TX_FIFO_WIDTH_32BIT;
        tx_config->fifo_threshold = 0;
        tx_config->logic0_pulse_width_1 = 0;
        tx_config->logic0_pulse_width_0 = 0;
        tx_config->logic1_pulse_width_1 = 2;
        tx_config->logic1_pulse_width_0 = 0;
        tx_config->head_pulse_width_1 = 7;
        tx_config->head_pulse_width_0 = 15;
        tx_config->tail_pulse_width_1 = 0;
        tx_config->tail_pulse_width_0 = 0;
        tx_config->pulse_width_unit = (ir_clock * 10 / 17777 - 1) & 0xfff;
    } else if (tx_config->tx_mode == IR_TX_RC5) {
        tx_config->data_bits = 13;
        tx_config->tail_inverse = 0;
        tx_config->tail_enable = 0;
        tx_config->head_inverse = 1;
        tx_config->head_enable = 1;
        tx_config->logic1_inverse = 1;
        tx_config->logic0_inverse = 0;
        tx_config->data_enable = 1;
        tx_config->swm_enable = 0;
        tx_config->output_modulation = 1;
        tx_config->output_inverse = 0;
        tx_config->freerun_enable = 0;
        tx_config->continue_enable = 0;
        tx_config->fifo_width = IR_TX_FIFO_WIDTH_32BIT;
        tx_config->fifo_threshold = 0;
        tx_config->logic0_pulse_width_1 = 0;
        tx_config->logic0_pulse_width_0 = 0;
        tx_config->logic1_pulse_width_1 = 0;
        tx_config->logic1_pulse_width_0 = 0;
        tx_config->head_pulse_width_1 = 0;
        tx_config->head_pulse_width_0 = 0;
        tx_config->tail_pulse_width_1 = 0;
        tx_config->tail_pulse_width_0 = 0;
        tx_config->pulse_width_unit = (ir_clock * 10 / 11248 - 1) & 0xfff;
    } else if (tx_config->tx_mode == IR_TX_SWM) {
        tx_config->swm_enable = 1;
        tx_config->output_modulation = 1;
        tx_config->output_inverse = 0;
        tx_config->fifo_width = IR_TX_FIFO_WIDTH_32BIT;
        tx_config->fifo_threshold = 0;
    }

    if (tx_config->tx_mode != IR_TX_CUSTOMIZE) {
        tx_config->modu_width_1 = ((ir_clock / 11310 + 5) / 10 - 1) & 0xff;
        tx_config->modu_width_0 = ((ir_clock / 5655 + 5) / 10 - 1) & 0xff;
    } else {
        if (tx_config->output_modulation != 0 && tx_config->freerun_enable != 0) {
            tx_config->continue_enable = 0;
            if (tx_config->tail_pulse_width_1 < 5) {
                tx_config->tail_pulse_width_1 = 5;
            }
            if (tx_config->tail_pulse_width_0 < 5) {
                tx_config->tail_pulse_width_0 = 5;
            }
        }
    }

    reg_base = dev->reg_base;
    regval = (tx_config->pulse_width_unit & 0xfff) | tx_config->modu_width_1 << 16 | tx_config->modu_width_0 << 24;
    putreg32(regval, reg_base + IRTX_PULSE_WIDTH_OFFSET);

#if !defined(BL602) && !defined(BL702)
    regval = getreg32(reg_base + IR_FIFO_CONFIG_1_OFFSET);
    regval &= ~IR_TX_FIFO_TH_MASK;
    regval |= tx_config->fifo_threshold << IR_TX_FIFO_TH_SHIFT;
    putreg32(regval, reg_base + IR_FIFO_CONFIG_1_OFFSET);
#endif

    regval = getreg32(reg_base + IRTX_CONFIG_OFFSET);
#if defined(BL602) || defined(BL702)
    regval &= ~(IR_CR_IRTX_SWM_EN | IR_CR_IRTX_MOD_EN | IR_CR_IRTX_OUT_INV);
#else
    regval &= ~(IR_CR_IRTX_SWM_EN | IR_CR_IRTX_MOD_EN | IR_CR_IRTX_OUT_INV | IR_CR_IRTX_FRM_FRAME_SIZE_MASK);
#endif
    if (tx_config->swm_enable) {
        regval |= IR_CR_IRTX_SWM_EN;
    }
    if (tx_config->output_modulation) {
        regval |= IR_CR_IRTX_MOD_EN;
    }
    if (tx_config->output_inverse) {
        regval |= IR_CR_IRTX_OUT_INV;
    }
#if !defined(BL602) && !defined(BL702)
    regval |= (tx_config->fifo_width & 0x3) << IR_CR_IRTX_FRM_FRAME_SIZE_SHIFT;
#endif
    if (tx_config->tx_mode == IR_TX_SWM) {
        putreg32(regval, reg_base + IRTX_CONFIG_OFFSET);
        return;
    }
#if defined(BL602) || defined(BL702)
    regval &= IR_CR_IRTX_SWM_EN | IR_CR_IRTX_MOD_EN | IR_CR_IRTX_OUT_INV;
#else
    regval &= IR_CR_IRTX_SWM_EN | IR_CR_IRTX_MOD_EN | IR_CR_IRTX_OUT_INV | IR_CR_IRTX_FRM_FRAME_SIZE_MASK;
#endif
    regval |= (tx_config->data_bits - 1) << IR_CR_IRTX_DATA_NUM_SHIFT;
    if (tx_config->tail_inverse) {
        regval |= IR_CR_IRTX_TAIL_HL_INV;
    }
    if (tx_config->tail_enable) {
        regval |= IR_CR_IRTX_TAIL_EN;
    }
    if (tx_config->head_inverse) {
        regval |= IR_CR_IRTX_HEAD_HL_INV;
    }
    if (tx_config->head_enable) {
        regval |= IR_CR_IRTX_HEAD_EN;
    }
    if (tx_config->logic1_inverse) {
        regval |= IR_CR_IRTX_LOGIC1_HL_INV;
    }
    if (tx_config->logic0_inverse) {
        regval |= IR_CR_IRTX_LOGIC0_HL_INV;
    }
    if (tx_config->data_enable) {
        regval |= IR_CR_IRTX_DATA_EN;
    }
#if !defined(BL602) && !defined(BL702)
    if (tx_config->freerun_enable) {
        regval |= IR_CR_IRTX_FRM_EN;
    }
    if (tx_config->continue_enable) {
        regval |= IR_CR_IRTX_FRM_CONT_EN;
    }
#endif
    putreg32(regval, reg_base + IRTX_CONFIG_OFFSET);

#if defined(BL602) || defined(BL702)
    regval = (tx_config->tail_pulse_width_1 & 0xf) << 28 | \
             (tx_config->tail_pulse_width_0 & 0xf) << 24 | \
             (tx_config->head_pulse_width_1 & 0xf) << 20 | \
             (tx_config->head_pulse_width_0 & 0xf) << 16 | \
             (tx_config->logic1_pulse_width_1 & 0xf) << 12 | \
             (tx_config->logic1_pulse_width_0 & 0xf) << 8 | \
             (tx_config->logic0_pulse_width_1 & 0xf) << 4 | \
             (tx_config->logic0_pulse_width_0 & 0xf);
    putreg32(regval, reg_base + IRTX_PW_OFFSET);
#else
    regval = tx_config->logic0_pulse_width_0 | tx_config->logic0_pulse_width_1 << 8 | \
             tx_config->logic1_pulse_width_0 << 16 | tx_config->logic1_pulse_width_1 << 24;
    putreg32(regval, reg_base + IRTX_PW_0_OFFSET);

    regval = tx_config->head_pulse_width_0 | tx_config->head_pulse_width_1 << 8 | \
             tx_config->tail_pulse_width_0 << 16 | tx_config->tail_pulse_width_1 << 24;
    putreg32(regval, reg_base + IRTX_PW_1_OFFSET);
#endif
}

void bflb_ir_send(struct bflb_device_s *dev, uint32_t *data, uint32_t length)
{
    uint32_t reg_base;
    uint32_t regval;
#if !defined(BL602) && !defined(BL702)
    uint32_t i = 0;
#endif

    bflb_ir_txint_clear(dev);

    reg_base = dev->reg_base;
#if defined(BL602) || defined(BL702)
    putreg32(data[0], reg_base + IRTX_DATA_WORD0_OFFSET);
    if (length > 1) {
        putreg32(data[1], reg_base + IRTX_DATA_WORD1_OFFSET);
    }
#endif

    regval = getreg32(reg_base + IRTX_CONFIG_OFFSET);
    regval |= IR_CR_IRTX_EN;
    putreg32(regval, reg_base + IRTX_CONFIG_OFFSET);

#if !defined(BL602) && !defined(BL702)
    if ((regval & IR_CR_IRTX_FRM_EN) == 0) {
        length = length < 4 ? length : 4;
    }
    while(i < length){
        if (bflb_ir_get_txfifo_cnt(dev) > 0) {
            putreg32(data[i], reg_base + IR_FIFO_WDATA_OFFSET);
            i++;
        }
    }

    if ((getreg32(reg_base + IRTX_CONFIG_OFFSET) & IR_CR_IRTX_FRM_EN) == 0) {
        while((bflb_ir_get_txint_status(dev) & IR_TX_INTSTS_END) == 0){
            /* Waiting for sending */
        }
    } else {
        while(bflb_ir_get_txfifo_cnt(dev) < 4){
            /* Waiting for sending */
        }
    }
#else
    while((bflb_ir_get_txint_status(dev) & IR_TX_INTSTS_END) == 0){
        /* Waiting for sending */
    }
#endif

    regval &= ~IR_CR_IRTX_EN;
    putreg32(regval, reg_base + IRTX_CONFIG_OFFSET);

    bflb_ir_txint_clear(dev);
}

void bflb_ir_swm_send(struct bflb_device_s *dev, uint16_t *data, uint8_t length)
{
    uint32_t reg_base;
    uint32_t regval;
    uint16_t min_data = data[0];
#if defined(BL602) || defined(BL702)
    uint32_t count = (length + 7) / 8;
#else
    uint32_t count = (length + 3) / 4;
#endif
    uint32_t pwval = 0;
    uint32_t i, j;

    if (length > 128) {
        length = 128;
    }

    bflb_ir_txint_clear(dev);

    /* Search for min value */
    for (i = 1; i < length; i++) {
        if (min_data > data[i] && data[i] != 0) {
            min_data = data[i];
        }
    }

    /* Set min value as pulse width unit */
    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRTX_PULSE_WIDTH_OFFSET);
    regval &= ~IR_CR_IRTX_PW_UNIT_MASK;
    regval |= min_data << IR_CR_IRTX_PW_UNIT_SHIFT;
    putreg32(regval, reg_base + IRTX_PULSE_WIDTH_OFFSET);

#if defined(BL602) || defined(BL702)
    /* Set tx SWM pulse width data as multiples of pulse width unit */
    for (i = 0; i < count; i++) {
        pwval = 0;

        if (i < count - 1) {
            for (j = 0; j < 8; j++) {
                regval = ((2 * data[j + i * 8] + min_data) / (2 * min_data) - 1) & 0xf;
                pwval |= regval << (4 * j);
            }

            putreg32(pwval, reg_base + IRTX_SWM_PW_0_OFFSET + i * 4);
        } else {
            for (j = 0; j < length % 8; j++) {
                regval = ((2 * data[j + i * 8] + min_data) / (2 * min_data) - 1) & 0xf;
                pwval |= regval << (4 * j);
            }

            putreg32(pwval, reg_base + IRTX_SWM_PW_0_OFFSET + i * 4);
        }
    }
#endif

    regval = getreg32(reg_base + IRTX_CONFIG_OFFSET);
    regval &= ~IR_CR_IRTX_DATA_NUM_MASK;
    regval |= (length - 1) << IR_CR_IRTX_DATA_NUM_SHIFT;
    regval |= IR_CR_IRTX_EN;
    putreg32(regval, reg_base + IRTX_CONFIG_OFFSET);

#if !defined(BL602) && !defined(BL702)
    /* Calculate tx SWM pulse width data as multiples of pulse width unit */
    for (i = 0; i < count; i++) {
        pwval = 0;

        if (i < count - 1) {
            /* Put every four pulse width together as a 32-bit value to tx fifo */
            for (j = 0; j < 4; j++) {
                /* Every pulse width divided by pulse width unit */
                regval = (DIVIDE_ROUND(data[j + i * 4], min_data) - 1) & 0xff;
                /* Tx fifo 32-bit value: pwval[7:0]:first pulse width, pwval[15:8]:second pulse width... */
                pwval |= regval << (8 * j);
            }
        } else {
            /* Deal with pulse width data remained which is less than 4 */
            for (j = 0; j < length % 4; j++) {
                regval = (DIVIDE_ROUND(data[j + i * 4], min_data) - 1) & 0xff;
                pwval |= regval << (8 * j);
            }
        }

        /* Write to tx fifo */
        while(bflb_ir_get_txfifo_cnt(dev) == 0){}
        putreg32(pwval, reg_base + IR_FIFO_WDATA_OFFSET);
    }
#endif

    while((bflb_ir_get_txint_status(dev) & IR_TX_INTSTS_END) == 0){
        /* Waiting for sending */
    }

    regval = getreg32(reg_base + IRTX_CONFIG_OFFSET);
    regval &= ~IR_CR_IRTX_EN;
    putreg32(regval, reg_base + IRTX_CONFIG_OFFSET);

    bflb_ir_txint_clear(dev);
}

void bflb_ir_tx_enable(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRTX_CONFIG_OFFSET);
    if (enable) {
        regval |= IR_CR_IRTX_EN;
    } else {
        regval &= ~IR_CR_IRTX_EN;
    }
    putreg32(regval, reg_base + IRTX_CONFIG_OFFSET);
}

void bflb_ir_txint_mask(struct bflb_device_s *dev, uint8_t int_type, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRTX_INT_STS_OFFSET);
    if (mask) {
        regval |= (int_type & 0x7) << 8;
    } else {
        regval &= ~((int_type & 0x7) << 8);
    }
    putreg32(regval, reg_base + IRTX_INT_STS_OFFSET);
}

void bflb_ir_txint_clear(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRTX_INT_STS_OFFSET);
    regval |= IR_CR_IRTX_END_CLR;
    putreg32(regval, reg_base + IRTX_INT_STS_OFFSET);
}

uint32_t bflb_ir_get_txint_status(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;
    return (getreg32(reg_base + IRTX_INT_STS_OFFSET) & 0x7);
}

#if !defined(BL602) && !defined(BL702)
void bflb_ir_link_txdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IR_FIFO_CONFIG_0_OFFSET);
    if (enable) {
        regval |= IRTX_DMA_EN;
    } else {
        regval &= ~IRTX_DMA_EN;
    }
    putreg32(regval, reg_base + IR_FIFO_CONFIG_0_OFFSET);
}

uint8_t bflb_ir_get_txfifo_cnt(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;
    return ((getreg32(reg_base + IR_FIFO_CONFIG_1_OFFSET) & IR_TX_FIFO_CNT_MASK) >> IR_TX_FIFO_CNT_SHIFT);
}

void bflb_ir_txfifo_clear(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IR_FIFO_CONFIG_0_OFFSET);
    regval |= IR_TX_FIFO_CLR;
    putreg32(regval, reg_base + IR_FIFO_CONFIG_0_OFFSET);
}
#endif
#endif

#if !defined(BL702L)
void bflb_ir_rx_init(struct bflb_device_s *dev, const struct bflb_ir_rx_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t ir_clock;
    uint16_t data_threshold, end_threshold;

    if (bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_IR, 0)) {
        ir_clock = bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_IR, 0);
    } else {
        ir_clock = 2000000;
    }

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRRX_CONFIG_OFFSET);
    regval &= ~IR_CR_IRRX_MODE_MASK;
    regval |= (config->rx_mode & 0x3) << IR_CR_IRRX_MODE_SHIFT;
    if (config->input_inverse) {
        regval |= IR_CR_IRRX_IN_INV;
    } else {
        regval &= ~IR_CR_IRRX_IN_INV;
    }
    if (!config->deglitch_enable) {
        regval &= ~IR_CR_IRRX_DEG_EN;
    } else {
        regval |= IR_CR_IRRX_DEG_EN;
        regval &= ~IR_CR_IRRX_DEG_CNT_MASK;
        regval |= config->deglitch_cnt << IR_CR_IRRX_DEG_CNT_SHIFT;
    }
    putreg32(regval, reg_base + IRRX_CONFIG_OFFSET);

    if (config->rx_mode == IR_RX_NEC) {
        data_threshold = (ir_clock / 588 - 1) & 0xffff;
        end_threshold = (ir_clock / 222 - 1) & 0xffff;
    } else if (config->rx_mode == IR_RX_RC5) {
        data_threshold = (ir_clock / 750 - 1) & 0xffff;
        end_threshold = (ir_clock / 400 - 1) & 0xffff;
    } else {
        data_threshold = config->data_threshold;
        end_threshold = config->end_threshold;
    }
    regval = getreg32(reg_base + IRRX_PW_CONFIG_OFFSET);
    regval = end_threshold << IR_CR_IRRX_END_TH_SHIFT | data_threshold;
    putreg32(regval, reg_base + IRRX_PW_CONFIG_OFFSET);

#if !defined(BL602) && !defined(BL702)
    regval = getreg32(reg_base + IR_FIFO_CONFIG_1_OFFSET);
    regval &= ~IR_RX_FIFO_TH_MASK;
    regval |= config->fifo_threshold << IR_RX_FIFO_TH_SHIFT;
    putreg32(regval, reg_base + IR_FIFO_CONFIG_1_OFFSET);
#endif
}

uint8_t bflb_ir_receive(struct bflb_device_s *dev, uint64_t *data)
{
    uint32_t reg_base;
    uint32_t regval;

    bflb_ir_rxint_clear(dev);

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRRX_CONFIG_OFFSET);
    regval |= IR_CR_IRRX_EN;
    putreg32(regval, reg_base + IRRX_CONFIG_OFFSET);

    while((bflb_ir_get_rxint_status(dev) & IR_RX_INTSTS_END) == 0){
        /* Waiting for receiving */
    }

    regval &= ~IR_CR_IRRX_EN;
    putreg32(regval, reg_base + IRRX_CONFIG_OFFSET);

    bflb_ir_rxint_clear(dev);

    regval = getreg32(reg_base + IRRX_DATA_COUNT_OFFSET) & IR_STS_IRRX_DATA_CNT_MASK;
    if (regval <= 32) {
        *data = getreg32(reg_base + IRRX_DATA_WORD0_OFFSET);
    } else {
        *data = getreg32(reg_base + IRRX_DATA_WORD0_OFFSET) | (uint64_t)getreg32(reg_base + IRRX_DATA_WORD1_OFFSET) << 32;
    }

    return regval;
}

uint8_t bflb_ir_swm_receive(struct bflb_device_s *dev, uint16_t *data, uint8_t length)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t i = 0;

    bflb_ir_rxint_clear(dev);

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRRX_CONFIG_OFFSET);
    regval |= IR_CR_IRRX_EN;
    putreg32(regval, reg_base + IRRX_CONFIG_OFFSET);

    while((bflb_ir_get_rxint_status(dev) & IR_RX_INTSTS_END) == 0){
        if (bflb_ir_get_rxfifo_cnt(dev) != 0 && i < length) {
#if defined(BL602) || defined(BL702)
            data[i] = getreg32(reg_base + IRRX_SWM_FIFO_RDATA_OFFSET);
#else
            data[i] = getreg32(reg_base + IR_FIFO_RDATA_OFFSET);
#endif
            i++;
        }
    }

    regval = getreg32(reg_base + IRRX_CONFIG_OFFSET);
    regval &= ~IR_CR_IRRX_EN;
    putreg32(regval, reg_base + IRRX_CONFIG_OFFSET);

    bflb_ir_rxint_clear(dev);

    return(getreg32(reg_base + IRRX_DATA_COUNT_OFFSET) & IR_STS_IRRX_DATA_CNT_MASK);
}

void bflb_ir_rx_enable(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRRX_CONFIG_OFFSET);
    if (enable) {
        regval |= IR_CR_IRRX_EN;
    } else {
        regval &= ~IR_CR_IRRX_EN;
    }
    putreg32(regval, reg_base + IRRX_CONFIG_OFFSET);
}

void bflb_ir_rxint_mask(struct bflb_device_s *dev, uint8_t int_type, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRRX_INT_STS_OFFSET);
    if (mask) {
        regval |= (int_type & 0x7) << 8;
    } else {
        regval &= ~((int_type & 0x7) << 8);
    }
    putreg32(regval, reg_base + IRRX_INT_STS_OFFSET);
}

void bflb_ir_rxint_clear(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + IRRX_INT_STS_OFFSET);
    regval |= IR_CR_IRRX_END_CLR;
    putreg32(regval, reg_base + IRRX_INT_STS_OFFSET);
}

uint32_t bflb_ir_get_rxint_status(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;
    return (getreg32(reg_base + IRRX_INT_STS_OFFSET) & 0x7);
}

uint8_t bflb_ir_get_rxfifo_cnt(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;
#if defined(BL602) || defined(BL702)
    return ((getreg32(reg_base + IRRX_SWM_FIFO_CONFIG_0_OFFSET) & IR_RX_FIFO_CNT_MASK) >> IR_RX_FIFO_CNT_SHIFT);
#else
    return ((getreg32(reg_base + IR_FIFO_CONFIG_1_OFFSET) & IR_RX_FIFO_CNT_MASK) >> IR_RX_FIFO_CNT_SHIFT);
#endif
}

void bflb_ir_rxfifo_clear(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
#if defined(BL602) || defined(BL702)
    regval = getreg32(reg_base + IRRX_SWM_FIFO_CONFIG_0_OFFSET);
    regval |= IR_RX_FIFO_CLR;
    putreg32(regval, reg_base + IRRX_SWM_FIFO_CONFIG_0_OFFSET);
#else
    regval = getreg32(reg_base + IR_FIFO_CONFIG_0_OFFSET);
    regval |= IR_RX_FIFO_CLR;
    putreg32(regval, reg_base + IR_FIFO_CONFIG_0_OFFSET);
#endif
}
#endif

int bflb_ir_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    switch (cmd) {
        default:
            ret = -EPERM;
            break;
    }
    return ret;
}
