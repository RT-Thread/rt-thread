#ifndef _BFLB_PWM_V2_H
#define _BFLB_PWM_V2_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup PWM_V2
  * @{
  */

/** @defgroup PWM_CHANNEL pwm channel definition
  * @{
  */
#define PWM_CH0       0
#define PWM_CH1       1
#define PWM_CH2       2
#define PWM_CH3       3
#define PWM_V2_CH_MAX 4
/**
  * @}
  */

/** @defgroup PWM_POLARITY pwm polarity definition
  * @{
  */
#define PWM_POLARITY_ACTIVE_LOW  0
#define PWM_POLARITY_ACTIVE_HIGH 1
/**
  * @}
  */

/** @defgroup PWM_STATE pwm state definition
  * @{
  */
#define PWM_STATE_INACTIVE 0
#define PWM_STATE_ACTIVE   1
/**
  * @}
  */

/** @defgroup PWM_TRIG_SDC_SRC pwm trigger adc source definition
  * @{
  */
#define PWM_TRIG_ADC_SRC_CH0_L  0
#define PWM_TRIG_ADC_SRC_CH0_H  1
#define PWM_TRIG_ADC_SRC_CH1_L  2
#define PWM_TRIG_ADC_SRC_CH1_H  3
#define PWM_TRIG_ADC_SRC_CH2_L  4
#define PWM_TRIG_ADC_SRC_CH2_H  5
#define PWM_TRIG_ADC_SRC_CH3_L  6
#define PWM_TRIG_ADC_SRC_CH3_H  7
#define PWM_TRIG_ADC_SRC_PERIOD 8
#define PWM_TRIG_ADC_SRC_NONE   0xF
/**
  * @}
  */

/** @defgroup PWM_INTEN pwm interrupt enable definition
  * @{
  */
#define PWM_INTEN_CH0_L  (1 << 0)
#define PWM_INTEN_CH0_H  (1 << 1)
#define PWM_INTEN_CH1_L  (1 << 2)
#define PWM_INTEN_CH1_H  (1 << 3)
#define PWM_INTEN_CH2_L  (1 << 4)
#define PWM_INTEN_CH2_H  (1 << 5)
#define PWM_INTEN_CH3_L  (1 << 6)
#define PWM_INTEN_CH3_H  (1 << 7)
#define PWM_INTEN_PERIOD (1 << 8)
#define PWM_INTEN_BRAKE  (1 << 9)
#define PWM_INTEN_REPT   (1 << 10)
/**
  * @}
  */

/** @defgroup PWM_INTSTS pwm interrupt status definition
  * @{
  */
#define PWM_INTSTS_CH0_L  (1 << 0)
#define PWM_INTSTS_CH0_H  (1 << 1)
#define PWM_INTSTS_CH1_L  (1 << 2)
#define PWM_INTSTS_CH1_H  (1 << 3)
#define PWM_INTSTS_CH2_L  (1 << 4)
#define PWM_INTSTS_CH2_H  (1 << 5)
#define PWM_INTSTS_CH3_L  (1 << 6)
#define PWM_INTSTS_CH3_H  (1 << 7)
#define PWM_INTSTS_PERIOD (1 << 8)
#define PWM_INTSTS_BRAKE  (1 << 9)
#define PWM_INTSTS_REPT   (1 << 10)
/**
  * @}
  */

/** @defgroup PWM_INTCLR pwm interrupt clear definition
  * @{
  */
#define PWM_INTCLR_CH0_L  (1 << 0)
#define PWM_INTCLR_CH0_H  (1 << 1)
#define PWM_INTCLR_CH1_L  (1 << 2)
#define PWM_INTCLR_CH1_H  (1 << 3)
#define PWM_INTCLR_CH2_L  (1 << 4)
#define PWM_INTCLR_CH2_H  (1 << 5)
#define PWM_INTCLR_CH3_L  (1 << 6)
#define PWM_INTCLR_CH3_H  (1 << 7)
#define PWM_INTCLR_PERIOD (1 << 8)
#define PWM_INTCLR_BRAKE  (1 << 9)
#define PWM_INTCLR_REPT   (1 << 10)
/**
  * @}
  */

/** @defgroup PWM_CMD pwm feature control cmd definition
  * @{
  */
#define PWM_CMD_SET_TRIG_ADC_SRC       (0x01)
#define PWM_CMD_SET_EXT_BRAKE_POLARITY (0x02)
#define PWM_CMD_SET_EXT_BRAKE_ENABLE   (0x03)
#define PWM_CMD_SET_SW_BRAKE_ENABLE    (0x04)
#define PWM_CMD_SET_STOP_ON_REPT       (0x05)
#define PWM_CMD_SET_REPT_COUNT         (0x06)
/**
  * @}
  */

/**
 * @brief PWM channel configuration structure
 *
 * @param positive_polarity    PWM posotive channel polarity, use @ref PWM_POLARITY
 * @param negative_polarity    PWM negative channel polarity, use @ref PWM_POLARITY
 * @param positive_stop_state  PWM posotive channel state when stop, use @ref PWM_STATE
 * @param negative_stop_state  PWM negative channel state when stop, use @ref PWM_STATE
 * @param positive_brake_state PWM posotive channel state when brake, use @ref PWM_STATE
 * @param negative_brake_state PWM negative channel state when brake, use @ref PWM_STATE
 * @param dead_time            PWM channel dead time
 */
struct bflb_pwm_v2_channel_config_s {
    uint8_t positive_polarity;
    uint8_t negative_polarity;
    uint8_t positive_stop_state;
    uint8_t negative_stop_state;
    uint8_t positive_brake_state;
    uint8_t negative_brake_state;
    uint8_t dead_time;
};

/**
 * @brief PWM configuration structure
 *
 * @param clk_source PWM clock source, use @ref BFLB_SYSTEM_CLOCK
 * @param clk_div    PWM clock dividor, should be in 1~65535
 * @param period     PWM period count, should be in 2~65535
 */
struct bflb_pwm_v2_config_s {
    uint8_t clk_source;
    uint16_t clk_div;
    uint16_t period;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize pwm.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to save pwm config
 */
void bflb_pwm_v2_init(struct bflb_device_s *dev, const struct bflb_pwm_v2_config_s *config);

/**
 * @brief Deinitialize pwm.
 *
 * @param [in] dev device handle
 */
void bflb_pwm_v2_deinit(struct bflb_device_s *dev);

/**
 * @brief Start pwm output.
 *
 * @param [in] dev device handle
 */
void bflb_pwm_v2_start(struct bflb_device_s *dev);

/**
 * @brief Stop pwm output.
 *
 * @param [in] dev device handle
 */
void bflb_pwm_v2_stop(struct bflb_device_s *dev);

/**
 * @brief Set pwm period to change pwm frequence. Frequcence(hz) = pwm source clock /div/period.
 *
 * @param [in] dev device handle
 * @param [in] period pwm period
 */
void bflb_pwm_v2_set_period(struct bflb_device_s *dev, uint16_t period);

/**
 * @brief Get pwm frequcency.
 *
 * @param [in] dev device handle
 * @return frequcency
 */
float bflb_pwm_v2_get_frequency(struct bflb_device_s *dev);

/**
 * @brief Config pwm channel.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] config pointer to save pwm channel config
 */
void bflb_pwm_v2_channel_init(struct bflb_device_s *dev, uint8_t ch, struct bflb_pwm_v2_channel_config_s *config);

/**
 * @brief Set pwm dutycycle. Dutycycle(%) = (high_threhold - low_threhold)/period * 100%.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] low_threhold pwm low threhold
 * @param [in] high_threhold pwm high threhold
 */
void bflb_pwm_v2_channel_set_threshold(struct bflb_device_s *dev, uint8_t ch, uint16_t low_threhold, uint16_t high_threhold);

/**
 * @brief Start pwm positive output.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void bflb_pwm_v2_channel_positive_start(struct bflb_device_s *dev, uint8_t ch);

/**
 * @brief Start pwm negative output.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void bflb_pwm_v2_channel_negative_start(struct bflb_device_s *dev, uint8_t ch);

/**
 * @brief Stop pwm positive output.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void bflb_pwm_v2_channel_positive_stop(struct bflb_device_s *dev, uint8_t ch);

/**
 * @brief Stop pwm negative output.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void bflb_pwm_v2_channel_negative_stop(struct bflb_device_s *dev, uint8_t ch);

/**
 * @brief Enable pwm interrupt.
 *
 * @param [in] dev device handle
 * @param [in] int_en interrupt type
 * @param [in] enable true means enable, otherwise disable
 */
void bflb_pwm_v2_int_enable(struct bflb_device_s *dev, uint32_t int_en, bool enable);

/**
 * @brief Get pwm interrupt status.
 *
 * @param [in] dev device handle
 * @return interrupt status, use @ref PWM_INTSTS
 */
uint32_t bflb_pwm_v2_get_intstatus(struct bflb_device_s *dev);

/**
 * @brief Clear pwm interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] int_clear clear value, use @ref PWM_INTCLR
 */
void bflb_pwm_v2_int_clear(struct bflb_device_s *dev, uint32_t int_clear);

/**
 * @brief Control pwm feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command, use @ref PWM_CMD
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int bflb_pwm_v2_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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