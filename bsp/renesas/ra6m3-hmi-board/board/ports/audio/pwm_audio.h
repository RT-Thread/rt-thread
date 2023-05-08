#ifndef _PWM_AUDIO_H_
#define _PWM_AUDIO_H_

#include <rtthread.h>

/**
 * @brief Configuration parameters of pwm audio for pwm_audio_init function
 */
typedef struct
{
    int gpio_num_left;                  /*!< the LEDC output gpio_num, Left channel */
    int gpio_num_right;                 /*!< the LEDC output gpio_num, Right channel */
//    ledc_channel_t ledc_channel_left;   /*!< LEDC channel (0 - 7), Corresponding to left channel*/
//    ledc_channel_t ledc_channel_right;  /*!< LEDC channel (0 - 7), Corresponding to right channel*/
//    ledc_timer_t ledc_timer_sel;        /*!< Select the timer source of channel (0 - 3) */
    uint8_t duty_resolution;            /*!< ledc pwm bits */
    uint32_t ringbuf_len;               /*!< ringbuffer size */

} pwm_audio_config_t;

/**
 * @brief pwm audio status
 */
typedef enum
{
    PWM_AUDIO_STATUS_UN_INIT = 0, /*!< PWM ?????? */
    PWM_AUDIO_STATUS_IDLE = 1, /*!< pwm audio idle */
    PWM_AUDIO_STATUS_BUSY = 2, /*!< pwm audio busy */
} pwm_audio_status_t;

/**
 * @brief Initializes and configure the pwm audio.
 *        Configure pwm audio with the given source.
 *
 * @param cfg Pointer of pwm_audio_config_t struct
 *
 * @return
 *     - ESP_OK Success
 */
rt_err_t pwm_audio_init(const pwm_audio_config_t *cfg);


rt_err_t pwm_audio_wait_complete(rt_tick_t ticks_to_wait);

/**
 * @brief Start audio play
 *
 * @return
 *     - ESP_OK Success
 */
rt_err_t pwm_audio_start(void);

/**
 * @brief Write data
 *
 * @param inbuf
 * @param len
 * @param bytes_written
 * @param ticks_to_wait
 *
 * @return
 *     - ESP_OK Success
 */
rt_err_t pwm_audio_write(uint8_t *inbuf, size_t len, size_t *bytes_written, rt_tick_t ticks_to_wait);

/**
 * @brief stop audio play
 *
 * @return
 *     - ESP_OK Success
 */
rt_err_t pwm_audio_stop(void);

/**
 * @brief Deinit pwm, timer and gpio
 *
 * @return
 *     - ESP_OK Success
 */
rt_err_t pwm_audio_deinit(void);

/**
 * @brief Set parameter for pwm audio.
 *
 * Similar to pwm_audio_set_sample_rate(), but also sets bit width.
 *
 * @param rate sample rate (ex: 8000, 44100...)
 * @param bits bit width
 * @param ch channel number
 *
 * @return
 *     - ESP_OK              Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
rt_err_t pwm_audio_set_param(int rate, uint8_t bits, int ch);

/**
 * @brief Set samplerate for pwm audio.
 *
 * @param rate sample rate (ex: 8000, 44100...)
 *
 * @return
 *     - ESP_OK              Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
rt_err_t pwm_audio_set_sample_rate(int rate);

/**
 * @brief Set volume for pwm audio.
 *        !!!Using volume greater than 0 may cause variable overflow and distortion!!!
 *        Usually you should enter a volume less than or equal to 0
 *
 * @param volume Volume to set (-16 ~ 16), see Macro VOLUME_0DB
 *        Set to 0 for original output;
 *        Set to less then 0 for attenuation, and -16 is mute;
 *        Set to more than 0 for enlarge, and 16 is double output
 *
 * @return
 *     - ESP_OK              Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
rt_err_t pwm_audio_set_volume(int8_t volume);

/**
 * @brief Get parameter for pwm audio.
 *
 * @param rate sample rate
 * @param bits bit width
 * @param ch channel number
 *
 * @return
 *     - ESP_OK              Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
rt_err_t pwm_audio_get_param(int *rate, int *bits, int *ch);

/**
 * @brief get pwm audio status
 *
 * @param status current pwm_audio status
 *
 * @return
 *     - ESP_OK Success
 */
rt_err_t pwm_audio_get_status(pwm_audio_status_t *status);

#endif
