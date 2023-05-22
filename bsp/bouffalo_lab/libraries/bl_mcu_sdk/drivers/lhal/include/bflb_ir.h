#ifndef _BFLB_IR_H
#define _BFLB_IR_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup IR
  * @{
  */

#if !defined(BL616)
/** @defgroup IR_TX_MODE ir tx mode definition
  * @{
  */
#define IR_TX_NEC       0
#define IR_TX_RC5       1
#define IR_TX_SWM       2
#define IR_TX_CUSTOMIZE 3
/**
  * @}
  */

/** @defgroup IR_TX_FIFO_WIDTH ir tx fifo width valid width definition
  * @{
  */
#if !defined(BL602) && !defined(BL702)
#define IR_TX_FIFO_WIDTH_8BIT  0
#define IR_TX_FIFO_WIDTH_16BIT 1
#define IR_TX_FIFO_WIDTH_24BIT 2
#endif
#define IR_TX_FIFO_WIDTH_32BIT 3
/**
  * @}
  */

/** @defgroup IR_TX_INTEN ir tx interrupt enable definition
  * @{
  */
#define IR_TX_INTEN_END (1 << 0)
#if !defined(BL602) && !defined(BL702)
#define IR_TX_INTEN_FIFO (1 << 1)
#define IR_TX_INTEN_FER  (1 << 2)
#endif
/**
  * @}
  */

/** @defgroup IR_TX_INTSTS ir tx interrupt status definition
  * @{
  */
#define IR_TX_INTSTS_END (1 << 0)
#if !defined(BL602) && !defined(BL702)
#define IR_TX_INTSTS_FIFO (1 << 1)
#define IR_TX_INTSTS_FER  (1 << 2)
#endif
/**
  * @}
  */

#endif

#if !defined(BL702L)
/** @defgroup IR_RX_MODE ir rx mode definition
  * @{
  */
#define IR_RX_NEC 0
#define IR_RX_RC5 1
#define IR_RX_SWM 2
/**
  * @}
  */

/** @defgroup IR_RX_INTEN ir rx interrupt enable definition
  * @{
  */
#define IR_RX_INTEN_END (1 << 0)
#if !defined(BL602) && !defined(BL702)
#define IR_RX_INTEN_FIFO (1 << 1)
#define IR_RX_INTEN_FER  (1 << 2)
#endif
/**
  * @}
  */

/** @defgroup IR_RX_INTSTS ir rx interrupt status definition
  * @{
  */
#define IR_RX_INTSTS_END (1 << 0)
#if !defined(BL602) && !defined(BL702)
#define IR_RX_INTSTS_FIFO (1 << 1)
#define IR_RX_INTSTS_FER  (1 << 2)
#endif
/**
  * @}
  */
#endif

#if !defined(BL616)
/**
 * @brief IR TX configuration structure
 *
 * @param tx_mode              TX mode select, use @ref IR_TX_MODE
 * @param data_bits            Bit count of data phase (don't care if tx freerun mode is enabled)
 * @param tail_inverse         Enable or disable signal of tail pulse inverse (don't care if SWM is enabled)
 * @param tail_enable          Enable or disable signal of tail pulse (don't care if SWM is enabled)
 * @param head_inverse         Enable or disable signal of head pulse inverse (don't care if SWM is enabled)
 * @param head_enable          Enable or disable signal of head pulse (don't care if SWM is enabled)
 * @param logic1_inverse       Enable or disable signal of logic 1 pulse inverse (don't care if SWM is enabled)
 * @param logic0_inverse       Enable or disable signal of logic 0 pulse inverse (don't care if SWM is enabled)
 * @param data_enable          Enable or disable signal of data pulse (don't care if SWM is enabled)
 * @param swm_enable           Enable or disable software mode(SWM)
 * @param output_modulation    Enable or disable signal of output modulation
 * @param output_inverse       Enable or disable signal of output inverse,0:output stays at low during idle state,1:stay at high
 * @param freerun_enable       Enable or disable tx freerun mode (don't care if SWM is enabled)
 * @param continue_enable      Disable:idle time between frames = (tailPulseWidth_0+tailPulseWidth_1)*pulseWidthUnit,Enable:no idle time between frames
 * @param fifo_width           IR frame size(also the valid width for each fifo entry), use @ref IR_TX_FIFO_WIDTH
 * @param fifo_threshold       TX FIFO threshold
 * @param logic0_pulse_width_1 Pulse width of logic 0 pulse phase 1 (don't care if SWM is enabled)
 * @param logic0_pulse_width_0 Pulse width of logic 0 pulse phase 0 (don't care if SWM is enabled)
 * @param logic1_pulse_width_1 Pulse width of logic 1 pulse phase 1 (don't care if SWM is enabled)
 * @param logic1_pulse_width_0 Pulse width of logic 1 pulse phase 0 (don't care if SWM is enabled)
 * @param head_pulse_width_1   Pulse width of head pulse phase 1 (don't care if SWM is enabled)
 * @param head_pulse_width_0   Pulse width of head pulse phase 0 (don't care if SWM is enabled)
 * @param tail_pulse_width_1   Pulse width of tail pulse phase 1 (don't care if SWM is enabled)
 * @param tail_pulse_width_0   Pulse width of tail pulse phase 0 (don't care if SWM is enabled)
 * @param modu_width_1         Modulation phase 1 width
 * @param modu_width_0         Modulation phase 0 width
 * @param pulse_width_unit     Pulse width unit
 */
struct bflb_ir_tx_config_s {
    uint8_t tx_mode;
    uint8_t data_bits;
    uint8_t tail_inverse;
    uint8_t tail_enable;
    uint8_t head_inverse;
    uint8_t head_enable;
    uint8_t logic1_inverse;
    uint8_t logic0_inverse;
    uint8_t data_enable;
    uint8_t swm_enable;
    uint8_t output_modulation;
    uint8_t output_inverse;
    uint8_t freerun_enable;
    uint8_t continue_enable;
    uint8_t fifo_width;
    uint8_t fifo_threshold;
    uint8_t logic0_pulse_width_1;
    uint8_t logic0_pulse_width_0;
    uint8_t logic1_pulse_width_1;
    uint8_t logic1_pulse_width_0;
    uint8_t head_pulse_width_1;
    uint8_t head_pulse_width_0;
    uint8_t tail_pulse_width_1;
    uint8_t tail_pulse_width_0;
    uint8_t modu_width_1;
    uint8_t modu_width_0;
    uint16_t pulse_width_unit;
};
#endif

#if !defined(BL702L)
/**
 * @brief IR RX configuration structure
 *
 * @param rx_mode         RX mode select, use @ref IR_RX_MODE
 * @param input_inverse   Enable or disable signal of input inverse
 * @param deglitch_enable Enable or disable signal of rx input de-glitch function
 * @param deglitch_cnt    De-glitch function cycle count
 * @param  data_threshold Pulse width threshold for logic 0/1 detection (don't care if SWM is enabled)
 * @param  end_threshold  Pulse width threshold to trigger end condition
 * @param  fifo_threshold RX FIFO threshold
 */
struct bflb_ir_rx_config_s {
    uint8_t rx_mode;
    uint8_t input_inverse;
    uint8_t deglitch_enable;
    uint8_t deglitch_cnt;
    uint16_t data_threshold;
    uint16_t end_threshold;
    uint16_t fifo_threshold;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(BL616)
/**
 * @brief Initialize ir tx.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to ir tx configure structure
 */
void bflb_ir_tx_init(struct bflb_device_s *dev, const struct bflb_ir_tx_config_s *config);

/**
 * @brief Send data in NEC/RC5/customize mode.
 *
 * @param [in] dev device handle
 * @param [in] data data buffer to send
 * @param [in] length length of data buffer
 */
void bflb_ir_send(struct bflb_device_s *dev, uint32_t *data, uint32_t length);

/**
 * @brief Send data in software mode.
 *
 * @param [in] dev device handle
 * @param [in] data data data buffer to send
 * @param [in] length length of data buffer
 */
void bflb_ir_swm_send(struct bflb_device_s *dev, uint16_t *data, uint8_t length);

/**
 * @brief Enable or disable ir tx.
 *
 * @param [in] dev device handle
 * @param [in] enable enable or disable
 */
void bflb_ir_tx_enable(struct bflb_device_s *dev, bool enable);

/**
 * @brief Mask or unmask ir tx interrupt.
 *
 * @param [in] dev device handle
 * @param [in] int_type ir tx interrupt type, use @ref IR_TX_INTEN
 * @param [in] mask mask or unmask
 */
void bflb_ir_txint_mask(struct bflb_device_s *dev, uint8_t int_type, bool mask);

/**
 * @brief Get ir tx interrupt status.
 *
 * @param [in] dev device handle
 * @return Ir tx interrupt status
 */
uint32_t bflb_ir_get_txint_status(struct bflb_device_s *dev);

/**
 * @brief Clear ir tx interrupt.
 *
 * @param [in] dev device handle
 */
void bflb_ir_txint_clear(struct bflb_device_s *dev);

#if !defined(BL602) && !defined(BL702)
/**
 * @brief Enable or disable ir tx dma mode.
 *
 * @param [in] dev device handle
 * @param [in] enable enable or disable
 */
void bflb_ir_link_txdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Get ir tx fifo available count.
 *
 * @param [in] dev device handle
 * @return Ir tx fifo available count
 */
uint8_t bflb_ir_get_txfifo_cnt(struct bflb_device_s *dev);

/**
 * @brief Clear ir tx fifo.
 *
 * @param [in] dev device handle
 */
void bflb_ir_txfifo_clear(struct bflb_device_s *dev);
#endif
#endif

#if !defined(BL702L)
/**
 * @brief Initialize ir rx.
 *
 * @param [in] dev device handle
 * @param [in] config config pointer to ir rx configure structure
 */
void bflb_ir_rx_init(struct bflb_device_s *dev, const struct bflb_ir_rx_config_s *config);

/**
 * @brief Receive data in NEC/RC5/customize mode.
 *
 * @param [in] dev device handle
 * @param [out] data data received
 * @return Bit count of data received
 */
uint8_t bflb_ir_receive(struct bflb_device_s *dev, uint64_t *data);

/**
 * @brief Receive data in software mode.
 *
 * @param [in] dev device handle
 * @param [out] data data buffer to receive
 * @param [in] length of data buffer
 * @return Length of data received
 */
uint8_t bflb_ir_swm_receive(struct bflb_device_s *dev, uint16_t *data, uint8_t length);

/**
 * @brief Enable or disable ir rx.
 *
 * @param [in] dev device handle
 * @param [in] enable enable or disable
 */
void bflb_ir_rx_enable(struct bflb_device_s *dev, bool enable);

/**
 * @brief Get ir rx fifo available count.
 *
 * @param [in] dev device handle
 * @return Ir rx fifo available count
 */
uint8_t bflb_ir_get_rxfifo_cnt(struct bflb_device_s *dev);

/**
 * @brief Clear ir rx fifo.
 *
 * @param [in] dev device handle
 */
void bflb_ir_rxfifo_clear(struct bflb_device_s *dev);

/**
 * @brief Mask ir rx interrupt.
 *
 * @param [in] dev device handle
 * @param [in] int_type ir rx interrupt type, use @ref IR_RX_INTEN
 * @param [in] mask mask or unmask
 */
void bflb_ir_rxint_mask(struct bflb_device_s *dev, uint8_t int_type, bool mask);

/**
 * @brief Get ir rx interrupt status.
 *
 * @param [in] dev device handle
 * @return Ir rx interrupt status
 */
uint32_t bflb_ir_get_rxint_status(struct bflb_device_s *dev);

/**
 * @brief Clear ir rx interrupt.
 *
 * @param [in] dev device handle
 */
void bflb_ir_rxint_clear(struct bflb_device_s *dev);

#endif

/**
 * @brief Control ir feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command
 * @param [in] arg user data
 * @return A negated errno value on failure
 */
int bflb_ir_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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
