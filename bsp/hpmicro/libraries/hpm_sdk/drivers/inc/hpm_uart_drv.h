/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_UART_DRV_H
#define HPM_UART_DRV_H
#include "hpm_common.h"
#include "hpm_uart_regs.h"
#include "hpm_soc_feature.h"

/**
 *
 * @brief UART driver APIs
 * @defgroup uart_interface UART driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief UART status
 */
enum {
    status_uart_no_suitable_baudrate_parameter_found = MAKE_STATUS(status_group_uart, 1),
};

/* @brief Parity */
typedef enum parity {
    parity_none = 0,
    parity_odd,
    parity_even,
    parity_always_1,
    parity_always_0,
} parity_setting_t;

/* @brief Stop bits */
typedef enum num_of_stop_bits {
    stop_bits_1 = 0,
    stop_bits_1_5,
    stop_bits_2,
} num_of_stop_bits_t;

/* @brief Word length */
typedef enum word_length {
    word_length_5_bits = 0,
    word_length_6_bits,
    word_length_7_bits,
    word_length_8_bits,
} word_length_t;

/* @brief UART fifo trigger levels */
typedef enum uart_fifo_trg_lvl {
    uart_rx_fifo_trg_not_empty = 0,
    uart_rx_fifo_trg_gt_one_quarter = 1,
    uart_rx_fifo_trg_gt_half = 2,
    uart_rx_fifo_trg_gt_three_quarters = 3,

    uart_tx_fifo_trg_not_full = 0,
    uart_tx_fifo_trg_lt_three_quarters = 1,
    uart_tx_fifo_trg_lt_half = 2,
    uart_tx_fifo_trg_lt_one_quarter = 3,
} uart_fifo_trg_lvl_t;

#if defined(UART_SOC_HAS_NEW_FIFO_THR) && (UART_SOC_HAS_NEW_FIFO_THR == 1)
/* @brief UART new fifo trigger levels */
typedef enum uart_new_fifo_trg_lvl {
    uart_fifo_1_byte  = 0,
    uart_fifo_2_bytes = 1,
    uart_fifo_3_bytes = 2,
    uart_fifo_4_bytes = 3,
    uart_fifo_5_bytes = 4,
    uart_fifo_6_bytes = 5,
    uart_fifo_7_bytes = 6,
    uart_fifo_8_bytes = 7,
    uart_fifo_9_bytes = 8,
    uart_fifo_10_bytes = 9,
    uart_fifo_11_bytes = 10,
    uart_fifo_12_bytes = 11,
    uart_fifo_13_bytes = 12,
    uart_fifo_14_bytes = 13,
    uart_fifo_15_bytes = 14,
    uart_fifo_16_bytes = 15,
} uart_new_fifo_trg_lvl_t;
#endif

/* @brief UART signals */
typedef enum uart_signal {
    uart_signal_rts = UART_MCR_RTS_MASK,
} uart_signal_t;

/* @brief UART signal levels */
typedef enum uart_signal_level {
    uart_signal_level_high,
    uart_signal_level_low,
} uart_signal_level_t;

/* @brief UART modem status */
typedef enum uart_modem_stat {
    uart_modem_stat_cts = UART_MSR_CTS_MASK,
    uart_modem_stat_dcts_changed = UART_MSR_DCTS_MASK,
} uart_modem_stat_t;

/* @brief UART interrupt enable masks */
typedef enum uart_intr_enable {
    uart_intr_rx_data_avail_or_timeout = UART_IER_ERBI_MASK,
    uart_intr_tx_slot_avail = UART_IER_ETHEI_MASK,
    uart_intr_rx_line_stat = UART_IER_ELSI_MASK,
    uart_intr_modem_stat = UART_IER_EMSI_MASK,
#if defined(UART_SOC_HAS_RXLINE_IDLE_DETECTION) && (UART_SOC_HAS_RXLINE_IDLE_DETECTION == 1)
    uart_intr_rx_line_idle = UART_IER_ERXIDLE_MASK,
#endif
} uart_intr_enable_t;

/* @brief UART interrupt IDs */
typedef enum uart_intr_id {
    uart_intr_id_modem_stat = 0x0,
    uart_intr_id_tx_slot_avail = 0x2,
    uart_intr_id_rx_data_avail = 0x4,
    uart_intr_id_rx_line_stat = 0x6,
    uart_intr_id_rx_timeout = 0xc,
} uart_intr_id_t;

/* @brief UART status */
typedef enum uart_stat {
    uart_stat_data_ready = UART_LSR_DR_MASK, /* rx data ready in fifo */
    uart_stat_overrun_error = UART_LSR_OE_MASK,
    uart_stat_parity_error = UART_LSR_PE_MASK,
    uart_stat_framing_error = UART_LSR_FE_MASK,
    uart_stat_line_break = UART_LSR_LBREAK_MASK,
    uart_stat_tx_slot_avail = UART_LSR_THRE_MASK,
    uart_stat_transmitter_empty = UART_LSR_TEMT_MASK,
    uart_stat_rx_fifo_error = UART_LSR_ERRF_MASK,
} uart_stat_t;

/**
 * @brief UART modem config
 */
typedef struct uart_modem_config {
    bool auto_flow_ctrl_en;     /**< Auto flow control enable flag */
    bool loop_back_en;          /**< Loop back enable flag */
    bool set_rts_high;          /**< Set signal RTS level high flag */
} uart_modem_config_t;

#if defined(UART_SOC_HAS_RXLINE_IDLE_DETECTION) && (UART_SOC_HAS_RXLINE_IDLE_DETECTION == 1)
/**
 * @brief UART RX Line Idle detection conditions
 */
typedef enum hpm_uart_rxline_idle_cond {
    uart_rxline_idle_cond_rxline_logic_one = 0,         /**< Treat as idle if the RX Line high duration exceeds threshold */
    uart_rxline_idle_cond_state_machine_idle = 1        /**< Treat as idle if the RX state machine idle state duration exceeds threshold */
} uart_rxline_idle_cond_t;

typedef struct hpm_uart_rxline_idle_detect_config {
    bool detect_enable;                 /**< RX Line Idle detection flag */
    bool detect_irq_enable;             /**< Enable RX Line Idle detection interrupt */
    uart_rxline_idle_cond_t idle_cond;  /**< RX Line Idle detection condition */
    uint8_t threshold;                  /**< UART RX Line Idle detection threshold, in terms of bits */
} uart_rxline_idle_config_t;
#endif

/**
 * @brief UART config
 */
typedef struct hpm_uart_config {
    uint32_t src_freq_in_hz;                    /**< Source clock frequency in Hz */
    uint32_t baudrate;                          /**< Baudrate */
    uint8_t num_of_stop_bits;                   /**< Number of stop bits */
    uint8_t word_length;                        /**< Word length */
    uint8_t parity;                             /**< Parity */
    uint8_t tx_fifo_level;                      /**< TX Fifo level */
    uint8_t rx_fifo_level;                      /**< RX Fifo level */
#if defined(UART_SOC_HAS_NEW_FIFO_THR) && (UART_SOC_HAS_NEW_FIFO_THR == 1)
    bool using_new_fifo_thr;
#endif
    bool dma_enable;                            /**< DMA Enable flag */
    bool fifo_enable;                           /**< Fifo Enable flag */
    uart_modem_config_t modem_config;           /**< Modem config */
#if defined(UART_SOC_HAS_RXLINE_IDLE_DETECTION) && (UART_SOC_HAS_RXLINE_IDLE_DETECTION == 1)
    uart_rxline_idle_config_t  rxidle_config;   /**< RX Idle configuration */
#endif
#if defined(UART_SOC_HAS_RXEN_CFG) && (UART_SOC_HAS_RXEN_CFG == 1)
    bool rx_enable;                             /**< RX Enable configuration */
#endif
} uart_config_t;

#if defined(UART_SOC_HAS_NEW_FIFO_THR) && (UART_SOC_HAS_NEW_FIFO_THR == 1)
typedef struct {
    uint16_t stop_bit_len;
    bool en_stop_bit_insert;
    bool hardware_trig;
    bool trig_mode;
    bool trig_clr_rxfifo;
} uart_trig_config_t;
#endif

typedef struct {
    uint8_t tx_fifo_level;                      /**< TX Fifo level */
    uint8_t rx_fifo_level;                      /**< RX Fifo level */
    bool reset_tx_fifo;                         /**< reset tx Fifo */
    bool reset_rx_fifo;                         /**< reset rx Fifo */
    bool dma_enable;                            /**< DMA Enable flag */
    bool fifo_enable;                           /**< Fifo Enable flag */
} uart_fifo_ctrl_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get fifo size
 *
 * @param [in] ptr UART base address
 * @retval size of Fifo
 */
static inline uint8_t uart_get_fifo_size(UART_Type *ptr)
{
    return 16 << ((ptr->CFG & UART_CFG_FIFOSIZE_MASK) >> UART_CFG_FIFOSIZE_SHIFT);
}

/**
 * @brief uart config fifo control
 *
 * @note fifo control register is WO access, prepare all bitfiled value to write
 *
 * @param [in] ptr UART base address
 * @param [in] ctrl uart_fifo_ctrl_t
 */
void uart_config_fifo_ctrl(UART_Type *ptr, uart_fifo_ctrl_t *ctrl);

/**
 * @brief uart clear rx fifo by reading data
 *
 * @note read out all data in rx fifo, the uart_intr_rx_data_avail_or_timeout is cleared
 * when RBR register is read
 *
 * @param [in] ptr UART base address
 */
static inline void uart_clear_rx_fifo(UART_Type *ptr)
{
    while (ptr->LSR & UART_LSR_DR_MASK) {
        ptr->RBR;
    }
}

/**
 * @brief Reset TX Fifo
 *
 * @note this API may modify other bit fields in FIFO control register
 *
 * @param [in] ptr UART base address
 */
static inline void uart_reset_tx_fifo(UART_Type *ptr)
{
    ptr->FCR = UART_FCR_TFIFORST_MASK;
}

/**
 * @brief Reset RX Fifo
 *
 * @note this API may modify other bit fields in FIFO control register
 *
 * @param [in] ptr UART base address
 */
static inline void uart_reset_rx_fifo(UART_Type *ptr)
{
    ptr->FCR = UART_FCR_RFIFORST_MASK;
}

/**
 * @brief [in] Reset both TX and RX Fifo
 *
 * @note this API may modify other bit fields in FIFO control register
 *
 * @param [in] ptr UART base address
 */
static inline void uart_reset_all_fifo(UART_Type *ptr)
{
    ptr->FCR = UART_FCR_RFIFORST_MASK | UART_FCR_TFIFORST_MASK;
}

/**
 * @brief Enable modem loopback
 *
 * @param [in] ptr UART base address
 */
static inline void uart_modem_enable_loopback(UART_Type *ptr)
{
    ptr->MCR |= UART_MCR_LOOP_MASK;
}

/**
 * @brief Disable modem loopback
 *
 * @param [in] ptr UART base address
 */
static inline void uart_modem_disable_loopback(UART_Type *ptr)
{
    ptr->MCR &= ~UART_MCR_LOOP_MASK;
}

/**
 * @brief Disable modem auto flow control
 *
 * @param [in] ptr UART base address
 */

static inline void uart_modem_disable_auto_flow_control(UART_Type *ptr)
{
    ptr->MCR &= ~UART_MCR_AFE_MASK;
}

/**
 * @brief Enable modem auto flow control
 *
 * @param [in] ptr UART base address
 */
static inline void uart_modem_enable_auto_flow_control(UART_Type *ptr)
{
    ptr->MCR |= UART_MCR_AFE_MASK;
}

/**
 * @brief Configure modem
 *
 * @param [in] ptr UART base address
 * @param config Pointer to modem config struct
 */
static inline void uart_modem_config(UART_Type *ptr, uart_modem_config_t *config)
{
    ptr->MCR = UART_MCR_AFE_SET(config->auto_flow_ctrl_en)
        | UART_MCR_LOOP_SET(config->loop_back_en)
        | UART_MCR_RTS_SET(!config->set_rts_high);
}

/**
 * @brief Get modem status
 *
 * @param [in] ptr UART base address
 * @retval Current modem status
 */
static inline uint8_t uart_get_modem_status(UART_Type *ptr)
{
    return ptr->MSR;
}

/**
 * @brief Write byte to TX
 *
 * @param ptr UART base address
 * @param c data to be sent
 */
static inline void uart_write_byte(UART_Type *ptr, uint8_t c)
{
    ptr->THR = UART_THR_THR_SET(c);
}


/**
 * @brief Read byte from RX
 *
 * @param ptr UART base address
 * @retval RX byte
 */
static inline uint8_t uart_read_byte(UART_Type *ptr)
{
    return (ptr->RBR & UART_RBR_RBR_MASK);
}

/**
 * @brief Check modem status with given mask
 *
 * @param [in] ptr UART base address
 * @param mask Status mask value to be checked against
 * @retval true if any bit in given mask is set
 * @retval false if none of any bit in given mask is set
 */
static inline bool uart_check_modem_status(UART_Type *ptr, uart_modem_stat_t mask)
{
    return ((ptr->MSR & mask) != 0U) ? true : false;
}

/**
 * @brief Disable IRQ with mask
 *
 * @param [in] ptr UART base address
 * @param irq_mask IRQ mask value to be disabled
 */
static inline void uart_disable_irq(UART_Type *ptr, uart_intr_enable_t irq_mask)
{
    ptr->IER &= ~irq_mask;
}

/**
 * @brief Enable IRQ with mask
 *
 * @param [in] ptr UART base address
 * @param irq_mask IRQ mask value to be enabled
 */
static inline void uart_enable_irq(UART_Type *ptr, uart_intr_enable_t irq_mask)
{
    ptr->IER |= irq_mask;
}

/**
 * @brief Get Enabled IRQ
 *
 * @param [in] ptr UART base address
 * @return enabled irq
 */
static inline uint32_t uart_get_enabled_irq(UART_Type *ptr)
{
    return ptr->IER;
}

/**
 * @brief Get interrupt identification
 *
 * @param [in] ptr UART base address
 * @retval interrupt id
 */
static inline uint8_t uart_get_irq_id(UART_Type *ptr)
{
    return (ptr->IIR & UART_IIR_INTRID_MASK);
}

#if defined(UART_SOC_HAS_RXLINE_IDLE_DETECTION) && (UART_SOC_HAS_RXLINE_IDLE_DETECTION == 1)
/**
 * @brief Determine whether UART RX Line is idle
 * @param [in] ptr UART base address
 */
static inline bool uart_is_rxline_idle(UART_Type *ptr)
{
    return ((ptr->IIR & UART_IIR_RXIDLE_FLAG_MASK) != 0U) ? true : false;
}

/**
 * @brief Clear UART RX Line Idle Flag
 * @param [in] ptr UART base address
 */
static inline void uart_clear_rxline_idle_flag(UART_Type *ptr)
{
    ptr->IIR = UART_IIR_RXIDLE_FLAG_MASK; /* Write-1-Clear Logic */
}

/**
 * @brief Enable UART RX Idle Line detection logic
 * @param [in] ptr UART base address
 */
static inline void uart_enable_rxline_idle_detection(UART_Type *ptr)
{
    ptr->IDLE_CFG |= UART_IDLE_CFG_RX_IDLE_EN_MASK;
}

/**
 * @brief Disable UART RX Idle Line detection logic
 *
 * @param [in] ptr UART base address
 */
static inline void uart_disable_rxline_idle_detection(UART_Type *ptr)
{
    ptr->IDLE_CFG &= ~UART_IDLE_CFG_RX_IDLE_EN_MASK;
}

/**
 * @brief Configure UART RX Line detection
 * @param [in] ptr UART base address
 * @param [in] rxidle_config RXLine IDLE detection configuration
 * @retval status_success if no error occurs
 */
hpm_stat_t uart_init_rxline_idle_detection(UART_Type *ptr, uart_rxline_idle_config_t rxidle_config);

#endif

/**
 * @brief Get status
 *
 * @param [in] ptr UART base address
 * @retval current status
 */
static inline uint8_t uart_get_status(UART_Type *ptr)
{
    return ptr->LSR;
}

/**
 * @brief Check uart status according to the given status mask
 *
 * @param [in] ptr UART base address
 * @param mask Status mask value to be checked against
 * @retval true if any bit in given mask is set
 * @retval false if none of any bit in given mask is set
 */
static inline bool uart_check_status(UART_Type *ptr, uart_stat_t mask)
{
    return ((ptr->LSR & mask) != 0U) ? true : false;
}

/**
 * @brief Get default config
 *
 * @param [in] ptr UART base address
 * @param config Pointer to the buffer to save default values
 */
void uart_default_config(UART_Type *ptr, uart_config_t *config);

/**
 * @brief Initialization
 *
 * @param [in] ptr UART base address
 * @param config Pointer to config struct
 * @retval status_success only if it succeeds
 */
hpm_stat_t uart_init(UART_Type *ptr, uart_config_t *config);

/**
 * @brief Send one byte after checking thresh hold status
 *
 * @param [in] ptr UART base address
 * @param c Byte to be sent
 * @retval status_success only if it succeeds
 */
hpm_stat_t uart_send_byte(UART_Type *ptr, uint8_t c);

/**
 * @brief Receive one byte after checking data ready status
 *
 * @param [in] ptr UART base address
 * @param c Pointer to buffer to save the byte received on UART
 * @retval status_success only if it succeeds
 */
hpm_stat_t uart_receive_byte(UART_Type *ptr, uint8_t *c);

/**
 * @brief Set uart signal output level
 *
 * @param [in] ptr UART base address
 * @param signal Target signal
 * @param level Target signal level
 */
void uart_set_signal_level(UART_Type *ptr,
                           uart_signal_t signal,
                           uart_signal_level_t level);

/**
 * @brief Flush sending buffer/fifo
 *
 * @param [in] ptr UART base address
 * @retval status_success only if it succeeds
 */
hpm_stat_t uart_flush(UART_Type *ptr);

/**
 * @brief Receive bytes blocking
 *
 * @param [in] ptr UART base address
 * @param buf Pointer to the buffer to save received data
 * @param size_in_byte Size in byte to be sent
 * @retval status_success only if it succeeds
 */
hpm_stat_t uart_receive_data(UART_Type *ptr, uint8_t *buf, uint32_t size_in_byte);

/**
 * @brief Send bytes blocking
 *
 * @param [in] ptr UART base address
 * @param buf Pointer to the buffer to be sent
 * @param size_in_byte Size in byte to be sent
 * @retval status_success only if it succeeds
 */
hpm_stat_t uart_send_data(UART_Type *ptr, uint8_t *buf, uint32_t size_in_byte);

/**
 * @brief Sets UART baudrate.
 *
 * This function configures the UART module baud rate. This function is used to update
 * the UART module baud rate after the UART module is initialized by the uart_init.
 *
 * @param ptr UART base address
 * @param baudrate UART baudrate to be set
 * @param src_clock_hz UART clock source frequency in Hz.
 * @retval status_uart_no_suitable_baudrate_parameter_found Baudrate is not supported in the current clock source
 * @retval status_success Set baudrate succeeded.
 */
hpm_stat_t uart_set_baudrate(UART_Type *ptr, uint32_t baudrate, uint32_t src_clock_hz);


#if defined(UART_SOC_HAS_NEW_FIFO_THR) && (UART_SOC_HAS_NEW_FIFO_THR == 1)
/**
 * @brief Config uart trigger mode for communication
 *
 * This function is used to tomagawa communication, uart sent out data in fifo then generate interrupt after
 * received specify count of data into fifo.
 *
 * @param ptr UART base address
 * @param uart_trig_config_t config
 */
void uart_config_trig_mode(UART_Type *ptr, uart_trig_config_t *config);

/**
 * @brief uart trigger communication
 *
 * This function triggers uart communication, the communication configed by uart_config_trig_mode()
 *
 * @param ptr UART base address
 */
static inline void uart_trigger_communication(UART_Type *ptr)
{
    ptr->MOTO_CFG &= ~UART_MOTO_CFG_HWTRG_EN_MASK;
    ptr->MOTO_CFG |= UART_MOTO_CFG_SWTRG_MASK;
}

/**
 * @brief uart enable hardware trigger mode
 *
 * This function configures uart start communication by hardware trigger from motor periphrals
 *
 * @param ptr UART base address
 * @param bool enable
 */
static inline void uart_enable_hardware_trigger_mode(UART_Type *ptr, bool enable)
{
    if (enable) {
        ptr->MOTO_CFG |= UART_MOTO_CFG_HWTRG_EN_MASK;
    } else {
        ptr->MOTO_CFG &= ~UART_MOTO_CFG_HWTRG_EN_MASK;
    }
}
#endif

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif    /* HPM_UART_DRV_H */
