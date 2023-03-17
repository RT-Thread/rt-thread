#ifndef _BFLB_RTC_H
#define _BFLB_RTC_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup RTC
  * @{
  */

#define BFLB_RTC_SEC2TIME(s)    (s * 32768)
#define BFLB_RTC_TIME2SEC(time) (time / 32768)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set rtc alarming time.
 *
 * @param [in] dev device handle
 * @param [in] time alarming time, unit is (1/32768 s)
 */
void bflb_rtc_set_time(struct bflb_device_s *dev, uint64_t time);

/**
 * @brief Get rtc current time.
 *
 * @param [in] dev device handle
 * @return current rtc running time
 */
uint64_t bflb_rtc_get_time(struct bflb_device_s *dev);

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