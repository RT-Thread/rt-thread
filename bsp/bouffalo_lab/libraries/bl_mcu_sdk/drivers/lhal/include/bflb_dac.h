#ifndef _BFLB_DAC_H
#define _BFLB_DAC_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup DAC
  * @{
  */

/** @defgroup DAC_CLK_DIV dac clock div definition
  * @{
  */
#define DAC_CLK_DIV_16 0
#define DAC_CLK_DIV_32 1
#define DAC_CLK_DIV_64 3
#define DAC_CLK_DIV_1  4
/**
  * @}
  */

/** @defgroup DAC_CHANNEL dac channel select
  * @{
  */
#define DAC_CHANNEL_A (1 << 0)
#define DAC_CHANNEL_B (1 << 1)
/**
  * @}
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize dac frequence.
 *
 * @param [in] dev device handle
 * @param [in] frequence dac clock div, use @ref DAC_CLK_DIV
 */
void bflb_dac_init(struct bflb_device_s *dev, uint8_t clk_div);

/**
 * @brief Deinitialize dac.
 *
 * @param [in] dev device handle
 */
void bflb_dac_deinit(struct bflb_device_s *dev);

/**
 * @brief Enable dac tx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_dac_link_txdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Enable dac channel.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void bflb_dac_channel_enable(struct bflb_device_s *dev, uint8_t ch);

/**
 * @brief Disable dac channel.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void bflb_dac_channel_disable(struct bflb_device_s *dev, uint8_t ch);

/**
 * @brief Set dac output value
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] value output value
 */
void bflb_dac_set_value(struct bflb_device_s *dev, uint8_t ch, uint16_t value);

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