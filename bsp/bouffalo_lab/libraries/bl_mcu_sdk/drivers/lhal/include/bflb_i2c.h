#ifndef _BFLB_I2C_H
#define _BFLB_I2C_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/* Bit definitions for the flags field in struct bflb_i2c_msg_s
 *
 * START/STOP Rules:
 *
 * 1. The lower half I2C driver will always issue the START condition at the
 *    beginning of a message unless I2C_M_NOSTART flag is set in the
 *    message.
 *
 * 2. The lower half I2C driver will always issue the STOP condition at the
 *    end of the messages unless:
 *
 *    a. The I2C_M_NOSTOP flag is set in the message, OR
 *    b. The following message has the I2C_M_NOSTART flag set (meaning
 *       that following message is simply a continuation of the transfer).
 *
 * A proper I2C repeated start would then have I2C_M_NOSTOP set on msg[n]
 * and I2C_M_NOSTART *not* set on msg[n+1].  See the following table:
 *
 *   msg[n].flags  msg[n+1].flags Behavior
 *   ------------ --------------- -----------------------------------------
 *   0            0                Two normal, separate messages with STOP
 *                                 on msg[n] then START on msg[n+1]
 *   0*           I2C_M_NOSTART    Continuation of the same transfer (must
 *                                 be the same direction).  See NOTE below.
 *   NO_STOP      0                No STOP on msg[n]; repeated START on
 *                                 msg[n+1].
 *
 * * NOTE: NO_STOP is implied in this case and may or not be explicitly
 *   included in the msg[n] flags
 */

#define I2C_M_READ    0x0001 /* Read data, from slave to master */
#define I2C_M_TEN     0x0002 /* Ten bit address */
#define I2C_M_DMA     0x0004 /* Enable dma mode */
#define I2C_M_NOSTOP  0x0040 /* Message should not end with a STOP */
#define I2C_M_NOSTART 0x0080 /* Message should not begin with a START */

/** @defgroup I2C_INTSTS i2c interrupt status definition
  * @{
  */
#define I2C_INTSTS_END     (1 << 0) /* Transfer end interrupt */
#define I2C_INTSTS_TX_FIFO (1 << 1) /* TX FIFO ready interrupt */
#define I2C_INTSTS_RX_FIFO (1 << 2) /* RX FIFO ready interrupt */
#define I2C_INTSTS_NACK    (1 << 3) /* NACK interrupt */
#define I2C_INTSTS_ARB     (1 << 4) /* Arbitration lost interrupt */
#define I2C_INTSTS_FER     (1 << 5) /* TX/RX FIFO error interrupt */
/**
 * @}
 */

/** @defgroup I2C_INTCLR i2c interrupt clear definition
  * @{
  */
#define I2C_INTCLR_END  (1 << 0) /* Transfer end interrupt */
#define I2C_INTCLR_NACK (1 << 3) /* NACK interrupt */
#define I2C_INTCLR_ARB  (1 << 4) /* Arbitration lost interrupt */
/**
 * @}
 */

/** @defgroup I2C_INTEN i2c interrupt enable definition
  * @{
  */
#define I2C_INTEN_END     (1 << 0) /* Transfer end interrupt */
#define I2C_INTEN_TX_FIFO (1 << 1) /* TX FIFO ready interrupt */
#define I2C_INTEN_RX_FIFO (1 << 2) /* RX FIFO ready interrupt */
#define I2C_INTEN_NACK    (1 << 3) /* NACK interrupt */
#define I2C_INTEN_ARB     (1 << 4) /* Arbitration lost interrupt */
#define I2C_INTEN_FER     (1 << 5) /* TX/RX FIFO error interrupt */
/**
 * @}
 */

/**
 * @brief I2C message structure
 *
 * @param addr          Slave address (7- or 10-bit)
 * @param flags         See I2C_M_* definitions
 * @param buffer        Buffer to be transferred
 * @param length        Length of the buffer in bytes, should be less than 256.
 */
struct bflb_i2c_msg_s {
    uint16_t addr;
    uint16_t flags;
    uint8_t *buffer;
    uint16_t length;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize i2c.
 *
 * @param [in] dev device handle
 * @param [in] frequency i2c frequency, range from 305Hz to 400KHz
 */
void bflb_i2c_init(struct bflb_device_s *dev, uint32_t frequency);

/**
 * @brief Deinitialize i2c.
 *
 * @param [in] dev device handle
 */
void bflb_i2c_deinit(struct bflb_device_s *dev);

/**
 * @brief Enable i2c tx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_i2c_link_txdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Enable i2c rx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_i2c_link_rxdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Start transferring i2c message.
 *
 * @param [in] dev device handle
 * @param [in] msgs pointer to i2c message
 * @param [in] count message count
 * @return A negated errno value on failure.
 */
int bflb_i2c_transfer(struct bflb_device_s *dev, struct bflb_i2c_msg_s *msgs, int count);

/**
 * @brief Enable or disable i2c interrupt.
 *
 * @param [in] dev device handle
 * @param [in] int_type interrupt type ,use @ref I2C_INTEN
 * @param [in] mask true means disable, false means enable
 */
void bflb_i2c_int_mask(struct bflb_device_s *dev, uint32_t int_type, bool mask);

/**
 * @brief Clear i2c interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] int_clear clear value, use @ref I2C_INTCLR
 */
void bflb_i2c_int_clear(struct bflb_device_s *dev, uint32_t int_clear);

/**
 * @brief Get i2c interrupt status.
 *
 * @param [in] dev device handle
 * @return interrupt status value, use @ref I2C_INTSTS
 */
uint32_t bflb_i2c_get_intstatus(struct bflb_device_s *dev);

/**
 * @brief Control i2c feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int bflb_i2c_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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
