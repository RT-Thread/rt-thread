/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-02-14     Rbb666        first version
 */
#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>
#include <rthw.h>

#include "pwm_audio.h"

#define BUFFER_MIN_SIZE     (256UL)
#define SAMPLE_RATE_MAX     (48000)
#define SAMPLE_RATE_MIN     (8000)
#define CHANNEL_LEFT_INDEX  (0)
#define CHANNEL_RIGHT_INDEX (1)
#define CHANNEL_LEFT_MASK   (0x01)
#define CHANNEL_RIGHT_MASK  (0x02)
#define VOLUME_0DB          (16)

typedef struct
{
    char *buf;                         /**< Original pointer */
    uint32_t volatile head;            /**< ending pointer */
    uint32_t volatile tail;            /**< Read pointer */
    uint32_t size;                     /**< Buffer size */
    uint32_t is_give;                  /**< semaphore give flag */
    rt_sem_t semaphore_rb;             /**< Semaphore for ringbuffer */

} ringBuf;
typedef ringBuf *ringbuf_handle_t;

typedef struct
{
    pwm_audio_config_t    config;                          /**< pwm audio config struct */
    timer_cfg_t           pwm_timer_cfg;                   /**< ledc timer config  */
    timer_cfg_t           gen_timer_cfg;                   /**< general timer config  */
    gpt_instance_ctrl_t   *pwm_timer_ctrl;                 /**< timer group register pointer */
    gpt_instance_ctrl_t   *gen_timer_ctrl;                 /**< timer group register pointer */
    ringbuf_handle_t      ringbuf;                         /**< audio ringbuffer pointer */
    uint32_t              channel_mask;                    /**< channel gpio mask */
    uint32_t              channel_set_num;                 /**< channel audio set number */
    int32_t               framerate;                       /*!< frame rates in Hz */
    int32_t               bits_per_sample;                 /*!< bits per sample (8, 16, 32) */
    int32_t               volume;                          /*!< the volume(-VOLUME_0DB ~ VOLUME_0DB) */
    rt_sem_t              sem_complete;                    /**< Semaphore for play complete */

    pwm_audio_status_t status;
} pwm_audio_handle;
typedef pwm_audio_handle *pwm_audio_handle_t;

/**< pwm audio handle pointer */
static pwm_audio_handle_t g_pwm_audio_handle = NULL;

/**
 * Ringbuffer for pwm audio
 */
static rt_err_t rb_destroy(ringbuf_handle_t rb)
{
    if (rb == NULL)
    {
        return RT_ERROR;
    }

    if (rb->buf)
    {
        rt_free(rb->buf);
        rb->buf = NULL;
    }

    if (rb->semaphore_rb)
    {
        rt_sem_delete(rb->semaphore_rb);
    }

    rt_free(rb);
    return RT_EOK;
}

static ringbuf_handle_t rb_create(uint32_t size)
{
    if (size < (BUFFER_MIN_SIZE << 2))
    {
        rt_kprintf("Invalid buffer size, Minimum = %d", (int32_t)(BUFFER_MIN_SIZE << 2));
        return NULL;
    }

    ringbuf_handle_t rb = NULL;
    char *buf = NULL;

    do
    {
        bool _success =
            (
                (rb                 = rt_malloc(sizeof(ringBuf)))   &&
                (buf                = rt_malloc(size))              &&
                (rb->semaphore_rb   = rt_sem_create("rb_sem", 0, RT_IPC_FLAG_PRIO))

            );

        if (!_success)
        {
            break;
        }

        rb->is_give = 0;
        rb->buf = buf;
        rb->head = rb->tail = 0;
        rb->size = size;
        return rb;

    }
    while (0);

    rb_destroy(rb);
    return NULL;
}

static uint32_t rb_get_count(ringbuf_handle_t rb)
{
    uint32_t tail = rb->tail;

    if (rb->head >= tail)
    {
        return (rb->head - tail);
    }

    return (rb->size - (tail - rb->head));
}

static uint32_t rb_get_free(ringbuf_handle_t rb)
{
    /** < Free a byte to judge the ringbuffer direction */
    return (rb->size - rb_get_count(rb) - 1);
}

static rt_err_t rb_flush(ringbuf_handle_t rb)
{
    rb->tail = rb->head = 0;
    return RT_EOK;
}

static rt_err_t rb_read_byte(ringbuf_handle_t rb, uint8_t *outdata)
{
    uint32_t tail = rb->tail;

    if (tail == rb->head)
    {
        return RT_ERROR;
    }

    // Send a byte from the buffer
    *outdata = rb->buf[tail];

    // Update tail position
    tail++;

    if (tail == rb->size)
    {
        tail = 0;
    }

    rb->tail = tail;
    return RT_EOK;
}

static rt_err_t rb_write_byte(ringbuf_handle_t rb, const uint8_t indata)
{
    // Calculate next head
    uint32_t next_head = rb->head + 1;

    if (next_head == rb->size)
    {
        next_head = 0;
    }

    if (next_head == rb->tail)
    {
        return RT_ERROR;
    }

    // Store data and advance head
    rb->buf[rb->head] = indata;
    rb->head = next_head;
    return RT_EOK;
}

static rt_err_t rb_wait_semaphore(ringbuf_handle_t rb, rt_tick_t ticks_to_wait)
{
    rb->is_give = 0; /**< As long as it's written, it's allowed to give semaphore again */

    if (rt_sem_take(rb->semaphore_rb, ticks_to_wait) == RT_EOK)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

rt_err_t pwm_audio_wait_complete(rt_tick_t ticks_to_wait)
{
    pwm_audio_handle_t handle = g_pwm_audio_handle;

    if (rt_sem_take(handle->sem_complete, ticks_to_wait) == RT_EOK)
    {
        return RT_EOK;
    }

    return RT_ERROR;
}

rt_err_t pwm_audio_init(const pwm_audio_config_t *cfg)
{
    rt_err_t res = RT_EOK;

    pwm_audio_handle_t handle = NULL;

    int level = rt_hw_interrupt_disable();

    handle = rt_malloc(sizeof(pwm_audio_handle));
    RT_ASSERT(handle != NULL);
    memset(handle, 0, sizeof(pwm_audio_handle));

    handle->ringbuf = rb_create(cfg->ringbuf_len);
    RT_ASSERT(handle->ringbuf != NULL);

    handle->sem_complete = rt_sem_create("pwm_cpl_sem", 0, RT_IPC_FLAG_PRIO);
    RT_ASSERT(handle->sem_complete != NULL);

    handle->config = *cfg;
    g_pwm_audio_handle = handle;

    handle->channel_mask = 0;

    if (handle->config.gpio_num_left >= 0)
    {
        handle->channel_mask |= CHANNEL_LEFT_MASK;
    }

    if (handle->config.gpio_num_right >= 0)
    {
        handle->channel_mask |= CHANNEL_RIGHT_MASK;
    }

    RT_ASSERT(0 != handle->channel_mask);

    //
    handle->pwm_timer_cfg = g_timer6_cfg;
    handle->pwm_timer_ctrl = &g_timer6_ctrl;

    R_GPT_Open(handle->pwm_timer_ctrl, &handle->pwm_timer_cfg);
    R_GPT_Start(handle->pwm_timer_ctrl);
    //

    /**< set a initial parameter */
//    res = pwm_audio_set_param(16000, 8, 2);

    handle->status = PWM_AUDIO_STATUS_IDLE;

    rt_hw_interrupt_enable(level);

    return res;
}

rt_err_t pwm_audio_set_param(int rate, uint8_t bits, int ch)
{
    rt_err_t res = RT_EOK;

    RT_ASSERT(g_pwm_audio_handle->status != PWM_AUDIO_STATUS_BUSY);
    RT_ASSERT(rate <= SAMPLE_RATE_MAX && rate >= SAMPLE_RATE_MIN);
    RT_ASSERT(bits == 32 || bits == 16 || bits == 8);
    RT_ASSERT(ch <= 2 && ch >= 1);

    pwm_audio_handle_t handle = g_pwm_audio_handle;

    handle->framerate = rate;
    handle->bits_per_sample = bits;
    handle->channel_set_num = ch;

    handle->gen_timer_cfg = g_timer2_cfg;
    handle->gen_timer_ctrl = &g_timer2_ctrl;

    timer_cfg_t *config = NULL;
    config = (struct st_timer_cfg *)&g_timer2_cfg;

    R_GPT_Open(handle->gen_timer_ctrl, &handle->gen_timer_cfg);
    R_GPT_Start(handle->gen_timer_ctrl);

    return res;
}

rt_err_t pwm_audio_set_volume(int8_t volume)
{
    if (volume < 0)
    {
        RT_ASSERT(-volume <= VOLUME_0DB);
    }
    else
    {
        RT_ASSERT(volume <= VOLUME_0DB);
    }

    pwm_audio_handle_t handle = g_pwm_audio_handle;
    handle->volume = volume + VOLUME_0DB;

    rt_kprintf("set volume to:%d\n", handle->volume);
    return RT_EOK;
}

rt_err_t pwm_audio_write(uint8_t *inbuf, size_t inbuf_len, size_t *bytes_written, rt_tick_t ticks_to_wait)
{
    rt_err_t res = RT_EOK;
    pwm_audio_handle_t handle = g_pwm_audio_handle;

    RT_ASSERT(inbuf != NULL && bytes_written != NULL && inbuf_len != 0);

    *bytes_written = 0;
    ringbuf_handle_t rb = handle->ringbuf;
    rt_tick_t start_ticks = rt_tick_get();

    while (inbuf_len)
    {
        if (RT_EOK == rb_wait_semaphore(rb, ticks_to_wait))
        {
            uint32_t free = rb_get_free(rb);
            uint32_t bytes_can_write = inbuf_len;

            if (inbuf_len > free)
            {
                bytes_can_write = free;
            }

            bytes_can_write &= 0xfffffffc;  /**< Aligned data, bytes_can_write should be an integral multiple of 4 */

            if (0 == bytes_can_write)
            {
                *bytes_written += inbuf_len;    /**< Discard the last misaligned bytes of data directly */
                return RT_EOK;
            }

            /**< Get the difference between PWM resolution and audio samplewidth */
            int8_t shift = handle->bits_per_sample - handle->config.duty_resolution;
            uint32_t len = bytes_can_write;

            switch (handle->bits_per_sample)
            {
            case 8:
            {
                if (shift < 0)
                {
                    /**< When the PWM resolution is greater than 8 bits, the value needs to be expanded */
                    uint16_t value;
                    uint8_t temp;
                    shift = -shift;
                    len >>= 1;
                    bytes_can_write >>= 1;

                    for (size_t i = 0; i < len; i++)
                    {
                        temp = (inbuf[i] * handle->volume / VOLUME_0DB) + 0x7f; /**< offset */
                        value = temp << shift;
                        rb_write_byte(rb, value);
                        rb_write_byte(rb, value >> 8);
                    }
                }
                else
                {
                    uint8_t value;

                    for (size_t i = 0; i < len; i++)
                    {
                        value = (inbuf[i] * handle->volume / VOLUME_0DB) + 0x7f; /**< offset */
                        rb_write_byte(rb, value);
                    }
                }
            }
            break;

            case 16:
            {
                len >>= 1;
                uint16_t *buf_16b = (uint16_t *)inbuf;
                static uint16_t value_16b;
                int16_t temp;

                if (handle->config.duty_resolution > 8)
                {
                    for (size_t i = 0; i < len; i++)
                    {
                        temp = buf_16b[i];
                        temp = temp * handle->volume / VOLUME_0DB;
                        value_16b = temp + 0x7fff; /**< offset */
                        value_16b >>= shift;
                        rb_write_byte(rb, value_16b);
                        rb_write_byte(rb, value_16b >> 8);
                    }
                }
                else
                {
                    /**
                     * When the PWM resolution is 8 bit, only one byte is transmitted
                     */
                    for (size_t i = 0; i < len; i++)
                    {
                        temp = buf_16b[i];
                        temp = temp * handle->volume / VOLUME_0DB;
                        value_16b = temp + 0x7fff; /**< offset */
                        value_16b >>= shift;
                        rb_write_byte(rb, value_16b);
                    }
                }
            }
            break;

            case 32:
            {
                len >>= 2;
                uint32_t *buf_32b = (uint32_t *)inbuf;
                uint32_t value;
                int32_t temp;

                if (handle->config.duty_resolution > 8)
                {
                    for (size_t i = 0; i < len; i++)
                    {
                        temp = buf_32b[i];
                        temp = temp * handle->volume / VOLUME_0DB;
                        value = temp + 0x7fffffff; /**< offset */
                        value >>= shift;
                        rb_write_byte(rb, value);
                        rb_write_byte(rb, value >> 8);
                    }
                }
                else
                {
                    /**
                     * When the PWM resolution is 8 bit, only one byte is transmitted
                     */
                    for (size_t i = 0; i < len; i++)
                    {
                        temp = buf_32b[i];
                        temp = temp * handle->volume / VOLUME_0DB;
                        value = temp + 0x7fffffff; /**< offset */
                        value >>= shift;
                        rb_write_byte(rb, value);
                    }
                }
            }
            break;
            default:
                break;
            }

            inbuf += bytes_can_write;
            inbuf_len -= bytes_can_write;
            *bytes_written += bytes_can_write;
        }
        else
        {
            res = RT_ERROR;
        }

        if ((rt_tick_get() - start_ticks) >= ticks_to_wait)
        {
            return res;
        }
    }

    return res;
}

/*
 * Note:
 * In order to improve efficiency, register is operated directly
 */
static inline void ledc_set_left_duty_fast(uint32_t duty_val)
{
    pwm_audio_handle_t handle = g_pwm_audio_handle;
//    *g_ledc_left_duty_val = (duty_val) << 4; /* Discard decimal part */
    R_GPT_DutyCycleSet(handle->pwm_timer_ctrl, duty_val, GPT_IO_PIN_GTIOCA);
}

static inline void ledc_set_right_duty_fast(uint32_t duty_val)
{
    pwm_audio_handle_t handle = g_pwm_audio_handle;
//    *g_ledc_right_duty_val = (duty_val) << 4; /* Discard decimal part */
    R_GPT_DutyCycleSet(handle->pwm_timer_ctrl, duty_val, GPT_IO_PIN_GTIOCB);
}

void cb_timer2(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();

    pwm_audio_handle_t handle = g_pwm_audio_handle;

    if (handle == NULL)
    {
        rt_kprintf("pwm audio not initialized\n");
        return;
    }

    static uint8_t wave_h, wave_l;
    static uint16_t value;
    ringbuf_handle_t rb = handle->ringbuf;

    /**
     * It is believed that the channel configured with GPIO needs to output sound
    */
    if (handle->channel_mask & CHANNEL_LEFT_MASK)
    {
        if (handle->config.duty_resolution > 8)
        {
            if (rb_get_count(rb) > 1)
            {
                rb_read_byte(rb, &wave_l);
                rb_read_byte(rb, &wave_h);
                value = ((wave_h << 8) | wave_l);
                ledc_set_left_duty_fast(value);/**< set the PWM duty */
            }
        }
        else
        {
            if (RT_EOK == rb_read_byte(rb, &wave_h))
            {
                ledc_set_left_duty_fast(wave_h);/**< set the PWM duty */
            }
        }
    }

    /**
     * If two gpios are configured, but the audio data has only one channel, copy the data to the right channel
     * Instead, the right channel data is discarded
    */
    if (handle->channel_mask & CHANNEL_RIGHT_MASK)
    {
        if (handle->channel_set_num == 1)
        {
            if (handle->config.duty_resolution > 8)
            {
                ledc_set_right_duty_fast(value);/**< set the PWM duty */
            }
            else
            {
                ledc_set_right_duty_fast(wave_h);/**< set the PWM duty */
            }
        }
        else
        {
            if (handle->config.duty_resolution > 8)
            {
                if (rb_get_count(rb) > 1)
                {
                    rb_read_byte(rb, &wave_l);
                    rb_read_byte(rb, &wave_h);
                    value = ((wave_h << 8) | wave_l);
                    ledc_set_right_duty_fast(value);/**< set the PWM duty */
                }
            }
            else
            {
                if (RT_EOK == rb_read_byte(rb, &wave_h))
                {
                    ledc_set_right_duty_fast(wave_h);/**< set the PWM duty */
                }
            }
        }
    }
    else
    {
        if (handle->channel_set_num == 2)
        {
            /**
             * Discard the right channel data only if the right channel is configured but the audio data is stereo
             * Read buffer but do nothing
             */
            if (handle->config.duty_resolution > 8)
            {
                if (rb_get_count(rb) > 1)
                {
                    rb_read_byte(rb, &wave_h);
                    rb_read_byte(rb, &wave_h);
                }
            }
            else
            {
                rb_read_byte(rb, &wave_h);
            }

            rb_read_byte(rb, &wave_l);
        }
    }

    /**
     * Send semaphore when buffer free is more than BUFFER_MIN_SIZE
     */
    if (0 == rb->is_give && rb_get_free(rb) > BUFFER_MIN_SIZE)
    {
        /**< The execution time of the following code is 2.71 microsecond */
        rb->is_give = 1; /**< To prevent multiple give semaphores */

        int err = -RT_ERROR;

        rt_interrupt_enter();
        err = rt_sem_release(rb->semaphore_rb);
        rt_interrupt_leave();

        if (rb_get_count(rb) <= 1)
        {
            rt_interrupt_enter();
            err = rt_sem_release(handle->sem_complete);
            rt_interrupt_leave();
        }
        if (err != RT_ERROR)
        {
            rt_thread_yield();
        }
    }

    rt_interrupt_leave();
}

rt_err_t pwm_audio_start(void)
{
    pwm_audio_handle_t handle = g_pwm_audio_handle;
    RT_ASSERT(NULL != handle);
    RT_ASSERT(handle->status == PWM_AUDIO_STATUS_IDLE);

    handle->status = PWM_AUDIO_STATUS_BUSY;

    /**< timer enable interrupt */
    int level = rt_hw_interrupt_disable();
    R_GPT_Start(handle->gen_timer_ctrl);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t pwm_audio_stop(void)
{
    pwm_audio_handle_t handle = g_pwm_audio_handle;

    /**< just disable timer ,keep pwm output to reduce switching nosie */
    /**< timer disable interrupt */
    int level = rt_hw_interrupt_disable();
    R_GPT_Stop(handle->gen_timer_ctrl);
    rt_hw_interrupt_enable(level);

    rb_flush(handle->ringbuf);  /**< flush ringbuf, avoid play noise */
    handle->status = PWM_AUDIO_STATUS_IDLE;
    return RT_EOK;
}

rt_err_t pwm_audio_deinit(void)
{
    pwm_audio_handle_t handle = g_pwm_audio_handle;
    RT_ASSERT(handle != NULL);

    handle->status = PWM_AUDIO_STATUS_UN_INIT;
    R_GPT_Close(handle->pwm_timer_ctrl);
    R_GPT_Close(handle->gen_timer_ctrl);
    rt_sem_delete(handle->sem_complete);
    rb_destroy(handle->ringbuf);
    rt_free(handle);
    return RT_EOK;
}
