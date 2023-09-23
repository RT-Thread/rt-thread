/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_uart_drv.h"

#define HPM_UART_DRV_RETRY_COUNT (5000U)
#define HPM_UART_MINIMUM_BAUDRATE (200U)

#ifndef HPM_UART_BAUDRATE_TOLERANCE
#define HPM_UART_BAUDRATE_TOLERANCE (3)
#endif

#define HPM_UART_OSC_MAX (32U)
#define HPM_UART_OSC_MIN (8U)
#define HPM_UART_BAUDRATE_DIV_MAX (0xFFFFU)
#define HPM_UART_BAUDRATE_DIV_MIN (1U)

void uart_default_config(UART_Type *ptr, uart_config_t *config)
{
    config->baudrate = 115200;
    config->word_length = word_length_8_bits;
    config->parity = parity_none;
    config->num_of_stop_bits = stop_bits_1;
    config->fifo_enable = true;
    config->rx_fifo_level = uart_rx_fifo_trg_not_empty;
    config->tx_fifo_level = uart_tx_fifo_trg_not_full;
    config->dma_enable = false;
    config->modem_config.auto_flow_ctrl_en = false;
    config->modem_config.loop_back_en = false;
    config->modem_config.set_rts_high = false;
#if defined(UART_SOC_HAS_RXLINE_IDLE_DETECTION) && (UART_SOC_HAS_RXLINE_IDLE_DETECTION == 1)
    config->rxidle_config.detect_enable = false;
    config->rxidle_config.detect_irq_enable = false;
    config->rxidle_config.idle_cond = uart_rxline_idle_cond_rxline_logic_one;
    config->rxidle_config.threshold = 10; /* 10-bit for typical UART configuration (8-N-1) */
#endif
#if defined(UART_SOC_HAS_RXEN_CFG) && (UART_SOC_HAS_RXEN_CFG == 1)
    config->rx_enable = true;
#endif
}

static bool uart_calculate_baudrate(uint32_t freq, uint32_t baudrate, uint16_t *div_out, uint8_t *osc_out)
{
    uint16_t div, osc, delta;
    float tmp;
    if ((div_out == NULL) || (!freq) || (!baudrate)
            || (baudrate < HPM_UART_MINIMUM_BAUDRATE)
            || (freq / HPM_UART_BAUDRATE_DIV_MIN < baudrate * HPM_UART_OSC_MIN)
            || (freq / HPM_UART_BAUDRATE_DIV_MAX > (baudrate * HPM_UART_OSC_MAX))) {
        return 0;
    }

    tmp = (float) freq / baudrate;

    for (uint8_t i = 0; i < HPM_UART_OSC_MAX; i += 2) {
        /* osc range: 0 - 32, even number */
        if (i == 0) {
            /* osc == 0 in bitfield, oversample rate is 32 */
            osc = HPM_UART_OSC_MAX;
        } else if (i <= 8) {
            /* osc <= 8 in bitfield, oversample rate is 8 */
            osc = HPM_UART_OSC_MIN;
        } else {
            /* osc > 8 && osc < 32 in bitfield, oversample rate is osc */
            osc = i;
        }
        delta = 0;
        div = (uint16_t)(tmp / osc);
        if (div < HPM_UART_BAUDRATE_DIV_MIN) {
            /* invalid div */
            continue;
        }
        if (div * osc > tmp) {
            delta = div * osc - tmp;
        } else if (div * osc < tmp) {
            delta = tmp - div * osc;
        }
        if (delta && ((delta * 100 / tmp) > HPM_UART_BAUDRATE_TOLERANCE)) {
            continue;
        } else {
            *div_out = div;
            *osc_out = (i <= 8 && i) ? osc : i;
            return true;
        }
    }
    return false;
}

hpm_stat_t uart_init(UART_Type *ptr, uart_config_t *config)
{
    uint32_t tmp;
    uint8_t osc;
    uint16_t div;

    /* disable all interrupts */
    ptr->IER = 0;
    /* Set DLAB to 1 */
    ptr->LCR |= UART_LCR_DLAB_MASK;

    if (!uart_calculate_baudrate(config->src_freq_in_hz, config->baudrate, &div, &osc)) {
        return status_uart_no_suitable_baudrate_parameter_found;
    }
    ptr->OSCR = (ptr->OSCR & ~UART_OSCR_OSC_MASK)
        | UART_OSCR_OSC_SET(osc);
    ptr->DLL = UART_DLL_DLL_SET(div >> 0);
    ptr->DLM = UART_DLM_DLM_SET(div >> 8);

    /* DLAB bit needs to be cleared once baudrate is configured */
    tmp = ptr->LCR & (~UART_LCR_DLAB_MASK);

    tmp &= ~(UART_LCR_SPS_MASK | UART_LCR_EPS_MASK | UART_LCR_PEN_MASK);
    switch (config->parity) {
    case parity_none:
        break;
    case parity_odd:
        tmp |= UART_LCR_PEN_MASK;
        break;
    case parity_even:
        tmp |= UART_LCR_PEN_MASK | UART_LCR_EPS_MASK;
        break;
    case parity_always_1:
        tmp |= UART_LCR_PEN_MASK | UART_LCR_SPS_MASK;
        break;
    case parity_always_0:
        tmp |= UART_LCR_EPS_MASK | UART_LCR_PEN_MASK
            | UART_LCR_SPS_MASK;
        break;
    default:
        /* invalid configuration */
        return status_invalid_argument;
    }

    tmp &= ~(UART_LCR_STB_MASK | UART_LCR_WLS_MASK);
    switch (config->num_of_stop_bits) {
    case stop_bits_1:
        break;
    case stop_bits_1_5:
        tmp |= UART_LCR_STB_MASK;
        break;
    case stop_bits_2:
        if (config->word_length < word_length_6_bits) {
            /* invalid configuration */
            return status_invalid_argument;
        }
        tmp |= UART_LCR_STB_MASK;
        break;
    default:
        /* invalid configuration */
        return status_invalid_argument;
    }

    ptr->LCR = tmp | UART_LCR_WLS_SET(config->word_length);

#if defined(UART_SOC_HAS_NEW_FIFO_THR) && (UART_SOC_HAS_NEW_FIFO_THR == 1)
    ptr->FCRR = UART_FCRR_TFIFORST_MASK | UART_FCRR_RFIFORST_MASK;
    if (config->fifo_enable) {
        /* Enable FIFO, reset TX and RX. */
        if (config->using_new_fifo_thr) {
            ptr->FCRR = UART_FCRR_FIFOT4EN_MASK
            | UART_FCRR_FIFOE_MASK
            | UART_FCRR_TFIFOT4_SET(config->tx_fifo_level)
            | UART_FCRR_RFIFOT4_SET(config->rx_fifo_level)
            | UART_FCRR_DMAE_SET(config->dma_enable);
        } else {
            ptr->FCR = UART_FCRR_FIFOE_MASK
            | UART_FCRR_TFIFOT_SET(config->tx_fifo_level)
            | UART_FCRR_RFIFOT_SET(config->rx_fifo_level)
            | UART_FCRR_DMAE_SET(config->dma_enable);
        }
    }
#else
    ptr->FCR = UART_FCR_TFIFORST_MASK | UART_FCR_RFIFORST_MASK;
    if (config->fifo_enable) {
        /* Enable FIFO, reset TX and RX. */
        ptr->FCR = UART_FCR_FIFOE_MASK
            | UART_FCR_TFIFOT_SET(config->tx_fifo_level)
            | UART_FCR_RFIFOT_SET(config->rx_fifo_level)
            | UART_FCR_DMAE_SET(config->dma_enable);
    }
#endif

    uart_modem_config(ptr, &config->modem_config);

#if defined(UART_SOC_HAS_RXLINE_IDLE_DETECTION) && (UART_SOC_HAS_RXLINE_IDLE_DETECTION == 1)
    uart_init_rxline_idle_detection(ptr, config->rxidle_config);
#endif
#if defined(UART_SOC_HAS_RXEN_CFG) && (UART_SOC_HAS_RXEN_CFG == 1)
    if (config->rx_enable) {
        ptr->IDLE_CFG |= UART_IDLE_CFG_RXEN_MASK;
    }
#endif
    return status_success;
}

hpm_stat_t uart_set_baudrate(UART_Type *ptr, uint32_t baudrate, uint32_t src_clock_hz)
{
    uint8_t osc;
    uint16_t div;

    /* Set DLAB to 1 */
    ptr->LCR |= UART_LCR_DLAB_MASK;

    if (!uart_calculate_baudrate(src_clock_hz, baudrate, &div, &osc)) {
        return status_uart_no_suitable_baudrate_parameter_found;
    }

    ptr->OSCR = (ptr->OSCR & ~UART_OSCR_OSC_MASK) | UART_OSCR_OSC_SET(osc);
    ptr->DLL = UART_DLL_DLL_SET(div >> 0);
    ptr->DLM = UART_DLM_DLM_SET(div >> 8);

    /* DLAB bit needs to be cleared once baudrate is configured */
    ptr->LCR &= ~UART_LCR_DLAB_MASK;

    return status_success;
}

hpm_stat_t uart_send_byte(UART_Type *ptr, uint8_t c)
{
    uint32_t retry = 0;

    while (!(ptr->LSR & UART_LSR_THRE_MASK)) {
        if (retry > HPM_UART_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_UART_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    ptr->THR = UART_THR_THR_SET(c);
    return status_success;
}

hpm_stat_t uart_flush(UART_Type *ptr)
{
    uint32_t retry = 0;

    while (!(ptr->LSR & UART_LSR_TEMT_MASK)) {
        if (retry > HPM_UART_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_UART_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    return status_success;
}

hpm_stat_t uart_receive_byte(UART_Type *ptr, uint8_t *byte)
{
    uint32_t retry = 0;

    while (!(ptr->LSR & UART_LSR_DR_MASK)) {
        if (retry > HPM_UART_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_UART_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    *byte = ptr->RBR & UART_RBR_RBR_MASK;
    return status_success;
}

void uart_set_signal_level(UART_Type *ptr, uart_signal_t signal, uart_signal_level_t level)
{
    if (level == uart_signal_level_low) {
        ptr->MCR = (ptr->MCR | signal);
    } else {
        ptr->MCR = (ptr->MCR & ~signal);
    }
}

hpm_stat_t uart_receive_data(UART_Type *ptr, uint8_t *source, uint32_t size_in_byte)
{
    for (uint32_t i = 0; i < size_in_byte; i++) {
        if (status_success != uart_receive_byte(ptr, source + i)) {
            return status_fail;
        }
    }
    return status_success;
}

hpm_stat_t uart_send_data(UART_Type *ptr, uint8_t *source, uint32_t size_in_byte)
{
    for (uint32_t i = 0; i < size_in_byte; i++) {
        if (status_success != uart_send_byte(ptr, *(source + i))) {
            return status_fail;
        }
    }
    return status_success;
}


#if defined(UART_SOC_HAS_RXLINE_IDLE_DETECTION) && (UART_SOC_HAS_RXLINE_IDLE_DETECTION == 1)
hpm_stat_t uart_init_rxline_idle_detection(UART_Type *ptr, uart_rxline_idle_config_t rxidle_config)
{
    ptr->IDLE_CFG = UART_IDLE_CFG_RX_IDLE_EN_SET(rxidle_config.detect_enable)
                      | UART_IDLE_CFG_RX_IDLE_THR_SET(rxidle_config.threshold)
                      | UART_IDLE_CFG_RX_IDLE_COND_SET(rxidle_config.idle_cond);

    if (rxidle_config.detect_irq_enable) {
        uart_enable_irq(ptr, uart_intr_rx_line_idle);
    } else {
        uart_disable_irq(ptr, uart_intr_rx_line_idle);
    }

    return status_success;
}
#endif

#if defined(UART_SOC_HAS_NEW_FIFO_THR) && (UART_SOC_HAS_NEW_FIFO_THR == 1)
void uart_config_trig_mode(UART_Type *ptr, uart_trig_config_t *config)
{
    ptr->MOTO_CFG &= ~UART_MOTO_CFG_TXSTP_BITS_MASK;

    ptr->MOTO_CFG = UART_MOTO_CFG_TXSTP_BITS_SET(config->stop_bit_len)
                    | UART_MOTO_CFG_HWTRG_EN_SET(config->hardware_trig)
                    | UART_MOTO_CFG_TRG_MODE_SET(config->trig_mode)
                    | UART_MOTO_CFG_TRG_CLR_RFIFO_SET(config->trig_clr_rxfifo)
                    | UART_MOTO_CFG_TXSTOP_INSERT_SET(config->en_stop_bit_insert);
}
#endif

/* FCR is WO register, preprae all bit field to write */
void uart_config_fifo_ctrl(UART_Type *ptr, uart_fifo_ctrl_t *ctrl)
{
    ptr->FCR =  UART_FCR_TFIFOT_SET(ctrl->tx_fifo_level)
                | UART_FCR_RFIFOT_SET(ctrl->rx_fifo_level)
                | UART_FCR_TFIFORST_SET(ctrl->reset_tx_fifo)
                | UART_FCR_RFIFORST_SET(ctrl->reset_rx_fifo)
                | UART_FCR_DMAE_SET(ctrl->dma_enable)
                | UART_FCR_FIFOE_SET(ctrl->fifo_enable);
}