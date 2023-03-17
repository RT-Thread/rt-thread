#ifndef _BFLB_WDG_H
#define _BFLB_WDG_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup WDG
  * @{
  */

#if !defined(BL702L)
#define WDG_CLKSRC_BCLK 0
#endif
#define WDG_CLKSRC_32K  1
#define WDG_CLKSRC_1K   2
#define WDG_CLKSRC_XTAL 3
#if !defined(BL702) && !defined(BL602)
#define WDG_CLKSRC_GPIO 4
#endif
#define WDG_CLKSRC_NO   5

/** @defgroup WDG_MODE Watch-dog reset/interrupt mode definition
  * @{
  */
#define WDG_MODE_INTERRUPT 0
#define WDG_MODE_RESET     1
/**
  * @}
  */

/**
 * @brief WDG configuration structure
 *
 * @param clock_source      Wdg clock source, use BFLB_SYSTEM_* definition
 * @param clock_div         Wdg clock divison value, from 0 to 255
 * @param comp_val          Wdg compare value
 * @param mode              Wdg reset/interrupt mode
 */
struct bflb_wdg_config_s {
    uint8_t clock_source;
    uint8_t clock_div;
    uint16_t comp_val;
    uint8_t mode;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize watchdog.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to save watchdog config
 */
void bflb_wdg_init(struct bflb_device_s *dev, const struct bflb_wdg_config_s *config);

/**
 * @brief Start watchdog.
 *
 * @param [in] dev device handle
 */
void bflb_wdg_start(struct bflb_device_s *dev);

/**
 * @brief Stop watchdog.
 *
 * @param [in] dev device handle
 */
void bflb_wdg_stop(struct bflb_device_s *dev);

/**
 * @brief Get watchdog counter value.
 *
 * @param [in] dev device handle
 * @return counter value
 */
uint16_t bflb_wdg_get_countervalue(struct bflb_device_s *dev);

/**
 * @brief Set watchdog counter value.
 *
 * @param [in] dev device handle
 * @param [in] counter value
 */
void bflb_wdg_set_countervalue(struct bflb_device_s *dev, uint16_t value);

/**
 * @brief Reset watchdog counter value.
 *
 * @param [in] dev device handle
 */
void bflb_wdg_reset_countervalue(struct bflb_device_s *dev);

/**
 * @brief Clear watchdog compare interrupt status.
 *
 * @param [in] dev device handle
 */
void bflb_wdg_compint_clear(struct bflb_device_s *dev);

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
