#ifndef _BFLB_I2S_H
#define _BFLB_I2S_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup I2S
  * @{
  */

/** @defgroup I2S_ROLE i2s role definition
  * @{
  */
#define I2S_ROLE_MASTER 0
#define I2S_ROLE_SLAVE  1
/**
  * @}
  */

/** @defgroup I2S_FORMAT_MODE i2s mode definition
  * @{
  */
#define I2S_MODE_LEFT_JUSTIFIED       0 /* left-justified or Phillips standard */
#define I2S_MODE_RIGHT_JUSTIFIED      1 /* right-justified */
#define I2S_MODE_DSP_SHORT_FRAME_SYNC 2 /* dsp modeA/B short frame sync */
#define I2S_MODE_DSP_LONG_FRAME_SYNC  3 /* dsp modeA/B long frame sync */
/**
  * @}
  */

/** @defgroup I2S_CHANNEL_MODE i2s mode definition
  * @{
  */
#define I2S_CHANNEL_MODE_NUM_1 0
#define I2S_CHANNEL_MODE_NUM_2 1
#define I2S_CHANNEL_MODE_NUM_3 2 /* only DSP mode, frame_size must equal data_size */
#define I2S_CHANNEL_MODE_NUM_4 3 /* only DSP mode, frame_size must equal data_size */
#define I2S_CHANNEL_MODE_NUM_6 4 /* only DSP mode, frame_size must equal data_size */
/**
  * @}
  */

/** @defgroup I2S_SLOT_WIDTH i2s slot width definition
  * @{
  */
#define I2S_SLOT_WIDTH_8  0
#define I2S_SLOT_WIDTH_16 1
#define I2S_SLOT_WIDTH_24 2
#define I2S_SLOT_WIDTH_32 3
/**
  * @}
  */

/** @defgroup I2S_INTSTS i2s interrupt status definition
  * @{
  */
#define I2S_INTSTS_TX_FIFO  (1 << 1)
#define I2S_INTSTS_RX_FIFO  (1 << 2)
#define I2S_INTSTS_FIFO_ERR (1 << 3)
/**
  * @}
  */

/** @defgroup I2S_CMD i2s feature control cmd definition
  * @{
  */
#define I2S_CMD_CLEAR_TX_FIFO    (0x01)
#define I2S_CMD_CLEAR_RX_FIFO    (0x02)
#define I2S_CMD_RX_DEGLITCH      (0x03)
#define I2S_CMD_DATA_ENABLE      (0x04)
#define I2S_CMD_CHANNEL_LR_MERGE (0x05)
#define I2S_CMD_CHANNEL_LR_EXCHG (0x06)
#define I2S_CMD_MUTE             (0x07)
#define I2S_CMD_BIT_REVERSE      (0x08)
/**
  * @}
  */

/** @defgroup I2S_CMD_DATA_ENABLE_TYPE i2s data enable type
  * @{
  */
#define I2S_CMD_DATA_ENABLE_TX (1 << 1)
#define I2S_CMD_DATA_ENABLE_RX (1 << 2)

/**
  * @}
  */

/**
 * @brief I2S configuration structure
 *
 * @param bclk_freq_hz        I2S bit frequence, Sampling_rate = bclk_freq_hz / frame_width / channel_num.
 * @param role                I2S role, use @ref I2S_ROLE
 * @param format_mode         I2S mode, use @ref I2S_FORMAT_MODE
 * @param channel_mode        I2S channel num, Only DSP mode supports more than 2 channels, use @ref I2S_CHANNEL_MODE
 * @param frame_width         I2S frame width, use @ref I2S_SLOT_WIDTH
 * @param data_width          I2S data order, frame_size must equal data_size in 3/4/6-channel mode, use @ref I2S_SLOT_WIDTH
 * @param fs_offset_cycle     I2S first bit offset of the data
 * @param tx_fifo_threshold   I2S tx fifo threshold, should be less than 16
 * @param rx_fifo_threshold   I2S rx fifo threshold, should be less than 16
 */
struct bflb_i2s_config_s {
    uint32_t bclk_freq_hz;
    uint8_t role;
    uint8_t format_mode;
    uint8_t channel_mode;
    uint8_t frame_width;
    uint8_t data_width;
    uint8_t fs_offset_cycle;

    uint8_t tx_fifo_threshold;
    uint8_t rx_fifo_threshold;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize i2s.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to save i2s config
 */
void bflb_i2s_init(struct bflb_device_s *dev, const struct bflb_i2s_config_s *config);

/**
 * @brief Deinitialize i2s.
 *
 * @param [in] dev device handle
 */
void bflb_i2s_deinit(struct bflb_device_s *dev);

/**
 * @brief Enable i2s tx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_i2s_link_txdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Enable i2s rx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_i2s_link_rxdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Enable or disable i2s rx fifo threhold interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_i2s_txint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Enable or disable i2s rx fifo threhold interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_i2s_rxint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Enable or disable i2s error interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_i2s_errint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Get i2s interrupt status.
 *
 * @param [in] dev device handle
 * @return interrupt status, use @ref I2S_INTSTS
 */
uint32_t bflb_i2s_get_intstatus(struct bflb_device_s *dev);

/**
 * @brief Control i2s feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command, use @ref I2S_CMD
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int bflb_i2s_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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
