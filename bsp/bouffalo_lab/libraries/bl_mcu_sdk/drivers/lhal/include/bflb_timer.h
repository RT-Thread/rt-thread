#ifndef _BFLB_TIMER_H
#define _BFLB_TIMER_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup TIMER
  * @{
  */

/** @defgroup TIMER_CLK_SOURCE timer clock source definition
  * @{
  */
#if !defined(BL702L)
#define TIMER_CLKSRC_BCLK 0
#endif
#define TIMER_CLKSRC_32K  1
#define TIMER_CLKSRC_1K   2
#define TIMER_CLKSRC_XTAL 3
#if !defined(BL702) && !defined(BL602)
#define TIMER_CLKSRC_GPIO 4
#endif
#define TIMER_CLKSRC_NO   5
/**
  * @}
  */

/** @defgroup TIMER_COUNTER_MODE timer counter mode definition
  * @{
  */
#define TIMER_COUNTER_MODE_PROLOAD 0
#define TIMER_COUNTER_MODE_UP      1
/**
  * @}
  */

/** @defgroup TIMER_COMP_ID timer compare id definition
  * @{
  */
#define TIMER_COMP_ID_0 0
#define TIMER_COMP_ID_1 1
#define TIMER_COMP_ID_2 2
#define TIMER_COMP_NONE 3
/**
  * @}
  */

/** @defgroup TIMER_CAPTURE_POLARITY timer capture polarity definition
  * @{
  */
#define TIMER_CAPTURE_POLARITY_POSITIVE 0
#define TIMER_CAPTURE_POLARITY_NEGATIVE 1
/**
  * @}
  */

/**
 * @brief TIMER configuration structure
 *
 * @param counter_mode      Timer counter mode, use @ref TIMER_COUNTER_MODE
 * @param clock_source      Timer clock source, use @ref TIMER_CLK_SOURCE
 * @param clock_div         Timer clock divison value, from 0 to 255
 * @param trigger_comp_id   Timer count register preload trigger source slelect, use @ref TIMER_COMP_ID
 * @param comp0_val         Timer compare 0 value
 * @param comp1_val         Timer compare 1 value
 * @param comp2_val         Timer compare 2 value
 * @param preload_val       Timer preload value
 */
struct bflb_timer_config_s {
    uint8_t counter_mode;
    uint8_t clock_source;
    uint8_t clock_div;
    uint8_t trigger_comp_id;
    uint32_t comp0_val;
    uint32_t comp1_val;
    uint32_t comp2_val;
    uint32_t preload_val;
};

/**
 * @brief TIMER capture configuration structure
 *
 * @param pin      Timer capture pin
 * @param polarity Timer capture polarity, use @ref TIMER_CAPTURE_POLARITY
 */
struct bflb_timer_capture_config_s {
    uint8_t pin;
    uint8_t polarity;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize timer.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to save timer config
 */
void bflb_timer_init(struct bflb_device_s *dev, const struct bflb_timer_config_s *config);

/**
 * @brief Deinitialize timer.
 *
 * @param [in] dev device handle
 */
void bflb_timer_deinit(struct bflb_device_s *dev);

/**
 * @brief Start timer.
 *
 * @param [in] dev device handle
 */
void bflb_timer_start(struct bflb_device_s *dev);

/**
 * @brief Stop timer.
 *
 * @param [in] dev device handle
 */
void bflb_timer_stop(struct bflb_device_s *dev);

/**
 * @brief Set timer preload value.
 *
 * @param [in] dev device handle
 * @param [in] val preload value
 */
void bflb_timer_set_preloadvalue(struct bflb_device_s *dev, uint32_t val);

/**
 * @brief Set compare value of corresponding compare id.
 *
 * @param [in] dev device handle
 * @param [in] cmp_no compare id, use @ref TIMER_COMP_ID
 * @param [in] val compare value
 */
void bflb_timer_set_compvalue(struct bflb_device_s *dev, uint8_t cmp_no, uint32_t val);

/**
 * @brief Get compare value of corresponding compare id.
 *
 * @param [in] dev device handle
 * @param [in] cmp_no compare id, use @ref TIMER_COMP_ID
 * @return uint32_t
 */
uint32_t bflb_timer_get_compvalue(struct bflb_device_s *dev, uint8_t cmp_no);

/**
 * @brief Get timer counter value.
 *
 * @param [in] dev device handle
 * @return counter value
 */
uint32_t bflb_timer_get_countervalue(struct bflb_device_s *dev);

/**
 * @brief Enable or disable timer interrupt of corresponding compare id.
 *
 * @param [in] dev device handle
 * @param [in] cmp_no compare id, use @ref TIMER_COMP_ID
 * @param [in] mask true means disable, false means enable
 */
void bflb_timer_compint_mask(struct bflb_device_s *dev, uint8_t cmp_no, bool mask);

/**
 * @brief Get timer interrupt status of corresponding compare id.
 *
 * @param [in] dev device handle
 * @param [in] cmp_no compare id, use @ref TIMER_COMP_ID
 * @return true mean yes, otherwise no.
 */
bool bflb_timer_get_compint_status(struct bflb_device_s *dev, uint8_t cmp_no);

/**
 * @brief Clear timer interrupt status of corresponding compare id.
 *
 * @param [in] dev device handle
 * @param [in] cmp_no compare id, use @ref TIMER_COMP_ID
 */
void bflb_timer_compint_clear(struct bflb_device_s *dev, uint8_t cmp_no);

#if !defined(BL702) || !defined(BL602)
void bflb_timer_capture_init(struct bflb_device_s *dev, const struct bflb_timer_capture_config_s *config);
uint32_t bflb_timer_capture_get_pulsewidth(struct bflb_device_s *dev);
#endif

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