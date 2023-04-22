#ifndef _BFLB_UART_H
#define _BFLB_UART_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup UART
  * @{
  */

/** @defgroup UART_DIRECTION uart direction enable definition
  * @{
  */
#define UART_DIRECTION_TX     (1 << 0)
#define UART_DIRECTION_RX     (1 << 1)
#define UART_DIRECTION_TXRX   (UART_DIRECTION_TX | UART_DIRECTION_RX)
#define UART_DIRECTION_MASK   UART_DIRECTION_TXRX
/**
  * @}
  */

/** @defgroup UART_DATABITS uart data bits definition
  * @{
  */
#define UART_DATA_BITS_5      0
#define UART_DATA_BITS_6      1
#define UART_DATA_BITS_7      2
#define UART_DATA_BITS_8      3
/**
  * @}
  */

/** @defgroup UART_STOPBITS uart stop bits definition
  * @{
  */
#define UART_STOP_BITS_0_5    0
#define UART_STOP_BITS_1      1
#define UART_STOP_BITS_1_5    2
#define UART_STOP_BITS_2      3
/**
  * @}
  */

/** @defgroup UART_PARITY uart parity definition
  * @{
  */
#define UART_PARITY_NONE      0
#define UART_PARITY_ODD       1
#define UART_PARITY_EVEN      2
#define UART_PARITY_MARK      3
#define UART_PARITY_SPACE     4
/**
  * @}
  */

/** @defgroup UART_BITORDER uart bitorder definition
  * @{
  */
#define UART_LSB_FIRST        0
#define UART_MSB_FIRST        1
/**
  * @}
  */

/** @defgroup UART_FLOWCTRL uart flow ctrl definition
  * @{
  */
#define UART_FLOWCTRL_NONE    0
#define UART_FLOWCTRL_RTS     (1 << 0)
#define UART_FLOWCTRL_CTS     (1 << 1)
#define UART_FLOWCTRL_RTS_CTS (UART_FLOWCTRL_RTS | UART_FLOWCTRL_CTS)
/**
  * @}
  */

/** @defgroup UART_INTSTS uart interrupt status definition
  * @{
  */
#define UART_INTSTS_TX_END    (1 << 0)
#define UART_INTSTS_RX_END    (1 << 1)
#define UART_INTSTS_TX_FIFO   (1 << 2)
#define UART_INTSTS_RX_FIFO   (1 << 3)
#define UART_INTSTS_RTO       (1 << 4)
#define UART_INTSTS_PCE       (1 << 5)
#define UART_INTSTS_TX_FER    (1 << 6)
#define UART_INTSTS_RX_FER    (1 << 7)
#if !defined(BL602)
#define UART_INTSTS_RX_LSE (1 << 8)
#endif
#if !defined(BL602) && !defined(BL702)
#define UART_INTSTS_RX_BCR (1 << 9)
#define UART_INTSTS_RX_ADS (1 << 10)
#define UART_INTSTS_RX_AD5 (1 << 11)
#endif
/**
  * @}
  */

/** @defgroup UART_INTCLR uart interrupt clear definition
  * @{
  */
#define UART_INTCLR_TX_END (1 << 0)
#define UART_INTCLR_RX_END (1 << 1)
#define UART_INTCLR_RTO    (1 << 4)
#define UART_INTCLR_PCE    (1 << 5)
#if !defined(BL602)
#define UART_INTCLR_RX_LSE (1 << 8)
#endif
#if !defined(BL602) && !defined(BL702)
#define UART_INTCLR_RX_BCR (1 << 9)
#define UART_INTCLR_RX_ADS (1 << 10)
#define UART_INTCLR_RX_AD5 (1 << 11)
#endif
/**
  * @}
  */

/** @defgroup UART_CMD uart feature control cmd definition
  * @{
  */
#define UART_CMD_SET_BAUD_RATE           (0x01)
#define UART_CMD_SET_DATA_BITS           (0x02)
#define UART_CMD_SET_STOP_BITS           (0x03)
#define UART_CMD_SET_PARITY_BITS         (0x04)
#define UART_CMD_CLR_TX_FIFO             (0x05)
#define UART_CMD_CLR_RX_FIFO             (0x06)
#define UART_CMD_SET_RTO_VALUE           (0x07)
#define UART_CMD_SET_RTS_VALUE           (0x08)
#define UART_CMD_GET_TX_FIFO_CNT         (0x09)
#define UART_CMD_GET_RX_FIFO_CNT         (0x0a)
#define UART_CMD_SET_AUTO_BAUD           (0x0b)
#define UART_CMD_GET_AUTO_BAUD           (0x0c)
#define UART_CMD_SET_BREAK_VALUE         (0x0d)
#define UART_CMD_SET_TX_LIN_VALUE        (0x0e)
#define UART_CMD_SET_RX_LIN_VALUE        (0x0f)
#define UART_CMD_SET_GLITCH_VALUE        (0x10)
#define UART_CMD_SET_TX_RS485_EN         (0x11)
#define UART_CMD_SET_TX_RS485_POLARITY   (0x12)
#define UART_CMD_SET_ABR_ALLOWABLE_ERROR (0x13)
#define UART_CMD_SET_SW_RTS_CONTROL      (0x14)
#define UART_CMD_IR_CONFIG               (0x15)
#define UART_CMD_SET_TX_FREERUN          (0x16)
#define UART_CMD_SET_TX_END_INTERRUPT    (0x17)
#define UART_CMD_SET_RX_END_INTERRUPT    (0x18)
#define UART_CMD_SET_TX_TRANSFER_LEN     (0x19)
#define UART_CMD_SET_RX_TRANSFER_LEN     (0x20)
#define UART_CMD_SET_TX_EN               (0x21)
#define UART_CMD_SET_BCR_END_INTERRUPT   (0x22)
#define UART_CMD_GET_BCR_COUNT           (0x23)
#define UART_CMD_SET_CTS_EN              (0x24)
#define UART_CMD_SET_TX_FIFO_THREHOLD    (0x25)
#define UART_CMD_SET_RX_FIFO_THREHOLD    (0x26)

/**
  * @}
  */

#define UART_AUTO_BAUD_START             0
#define UART_AUTO_BAUD_0X55              1

struct bflb_uart_ir_config_s {
    bool tx_en;
    bool rx_en;
    bool tx_inverse;
    bool rx_inverse;
    uint16_t tx_pluse_start;
    uint16_t tx_pluse_stop;
    uint16_t rx_pluse_start;
};

/**
 * @brief UART configuration structure
 *
 * @param baudrate          UART baudrate setting in bps,should be less than uart_clk/2
 * @param direction         UART direction, use @ref UART_DIRECTION
 * @param data_bits         UART data bits, use @ref UART_DATABITS
 * @param stop_bits         UART stop bits, use @ref UART_STOPBITS
 * @param parity            UART parity bit, use @ref UART_PARITY
 * @param bit_order         UART bit first, use @ref UART_BITORDER
 * @param flow_ctrl         UART flow control setting, use @ref UART_FLOWCTRL
 * @param tx_fifo_threshold UART tx fifo threshold, should be less than 32.
 * @param rx_fifo_threshold UART rx fifo threshold, should be less than 32.
 */
struct bflb_uart_config_s {
    uint32_t baudrate;
    uint8_t direction;
    uint8_t data_bits;
    uint8_t stop_bits;
    uint8_t parity;
    uint8_t bit_order;
    uint8_t flow_ctrl;
    uint8_t tx_fifo_threshold;
    uint8_t rx_fifo_threshold;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize uart.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to save uart config
 */
void bflb_uart_init(struct bflb_device_s *dev, const struct bflb_uart_config_s *config);

/**
 * @brief Deinitialize uart.
 *
 * @param [in] dev device handle
 */
void bflb_uart_deinit(struct bflb_device_s *dev);

/**
 * @brief Enable uart.
 *
 * @param [in] dev device handle
 */
void bflb_uart_enable(struct bflb_device_s *dev);

/**
 * @brief Disable uart.
 *
 * @param [in] dev device handle
 */
void bflb_uart_disable(struct bflb_device_s *dev);

/**
 * @brief Enable uart tx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_uart_link_txdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Enable uart rx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_uart_link_rxdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Put one char on uart.
 *
 * @param [in] dev device handle
 * @param [in] ch char
 * @return A negated errno value on failure.
 */
int bflb_uart_putchar(struct bflb_device_s *dev, int ch);

/**
 * @brief Get char from uart.
 *
 * @param [in] dev device handle
 * @return A negated errno value on failure, otherwise received char.
 */
int bflb_uart_getchar(struct bflb_device_s *dev);

/**
 * @brief Put a block of data on uart.This is a poll api.
 *
 * @param [in] dev device handle
 * @param [in] data pointer to save send data
 * @param [in] len length to send
 * @return A negated errno value on failure.
 */
int bflb_uart_put(struct bflb_device_s *dev, uint8_t *data, uint32_t len);

/**
 * @brief Get a block of data from uart. This is a asynchronous api.
 *
 * @param [in] dev device handle
 * @param [in] data pointer to save received data
 * @param [in] len max length wants to receive
 * @return actual received length
 */
int bflb_uart_get(struct bflb_device_s *dev, uint8_t *data, uint32_t len);

/**
 * @brief Check if there is free space in tx fifo.
 *
 * @param [in] dev device handle
 * @return Return true if the tranmsit hardware is ready to send another byte
 */
bool bflb_uart_txready(struct bflb_device_s *dev);

/**
 * @brief Check if there is no data in tx fifo.
 *
 * @param [in] dev device handle
 * @return Return true if all characters have been sent
 */
bool bflb_uart_txempty(struct bflb_device_s *dev);

/**
 * @brief Check if there is data in rx fifo.
 *
 * @param [in] dev device handle
 * @return true means yes.Otherwise there is no data in rx fifo
 */
bool bflb_uart_rxavailable(struct bflb_device_s *dev);

/**
 * @brief Enable or disable uart tx fifo threhold interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_uart_txint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Enable or disable uart rx fifo threhold interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_uart_rxint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Enable or disable uart error interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_uart_errint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Get uart interrupt status.
 *
 * @param [in] dev device handle
 * @return interrupt status, use @ref UART_INTSTS
 */
uint32_t bflb_uart_get_intstatus(struct bflb_device_s *dev);

/**
 * @brief Clear uart interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] int_clear clear value, use @ref UART_INTCLR
 */
void bflb_uart_int_clear(struct bflb_device_s *dev, uint32_t int_clear);

/**
 * @brief Control uart feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command, use @ref UART_CMD
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int bflb_uart_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif
