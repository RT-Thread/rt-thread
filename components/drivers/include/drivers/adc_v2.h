/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-21     wdfk-prog    add standalone adc v2 framework interface
 */

/**
 * @file adc_v2.h
 * @brief Standalone ADC V2 framework declarations.
 */

#ifndef __ADC_V2_H__
#define __ADC_V2_H__

#include <rtconfig.h>
#include "misc.h"
#if !defined(RT_USING_ADC_V2)
#error "ADC V2 interface requires RT_USING_ADC_V2."
#endif /* !defined(RT_USING_ADC_V2) */

#include <rtatomic.h>
#include <rtdevice.h>
#include <rtthread.h>

#if defined(RT_ADC_USING_TRIGGER)
#include <drivers/adc_v2_trigger.h>
#endif /* defined(RT_ADC_USING_TRIGGER) */

#if defined(RT_ADC_USING_STREAM) && defined(RT_ADC_STREAM_USING_FIFO)
#include <ipc/completion.h>
#include <ipc/ringbuffer.h>
#endif /* defined(RT_ADC_USING_STREAM) && defined(RT_ADC_STREAM_USING_FIFO) */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief ADC control command identifiers.
 */
enum rt_adc_control_cmd
{
    RT_ADC_CMD_GET_RESOLUTION = RT_DEVICE_CTRL_BASE(ADC) + 1, /**< Get resolution in bits. */
    RT_ADC_CMD_CALIBRATE,                                     /**< Run ADC calibration. */
    RT_ADC_CMD_SET_VREF,                                      /**< Set fallback VREF from rt_uint32_t mV. */
    RT_ADC_CMD_CALC_VREF,                                     /**< Calculate VDDA from a raw VREF sample. */
    RT_ADC_CMD_GET_VREF_CHANNEL,                              /**< Get the backend VREF sample channel as rt_uint8_t. */
    RT_ADC_CMD_SET_SESSION,                                   /**< Configure and cache conversion channels from rt_uint32_t mask. */
    RT_ADC_CMD_SET_CONFIG,                                    /**< Set backend private device configuration. */
    RT_ADC_CMD_GET_CONFIG,                                    /**< Get backend private device configuration. */
    RT_ADC_CMD_CLEAR_CHANNEL_CONFIG                           /**< Clear backend channel/rank configuration explicitly. */
};

/**
 * @brief ADC input mode request flags.
 */
enum rt_adc_input_mode
{
    RT_ADC_INPUT_MODE_SINGLE_ENDED = 0x01U, /**< Single-ended ADC input mode. */
    RT_ADC_INPUT_MODE_DIFFERENTIAL = 0x02U  /**< Differential ADC input mode. */
};

/**
 * @brief Build an ADC channel mask from one logical channel index.
 * @param _channel Logical ADC channel index.
 */
#define RT_ADC_CHANNEL_MASK(_channel) (1UL << (rt_uint32_t)(_channel))

/**
 * @brief ADC framework runtime state.
 */
enum rt_adc_state
{
    RT_ADC_STATE_IDLE = 0, /**< The ADC device is idle. */
    RT_ADC_STATE_LOCKED,  /**< The ADC device is temporarily locked by a framework operation. */
    RT_ADC_STATE_STREAM   /**< The ADC device is owned by an active stream session. */
};

struct rt_adc_device;
typedef struct rt_adc_device *rt_adc_device_t;

struct rt_adc_sequence_cfg;
struct rt_adc_stream_cfg;

/**
 * @brief ADC core driver operation table.
 */
struct rt_adc_core_ops
{
    /**
     * @brief Open and initialize the ADC hardware.
     * @param device Pointer to the ADC device object.
     * @return Operation status.
     */
    rt_err_t (*open)(struct rt_adc_device *device);

    /**
     * @brief Close and deinitialize the ADC hardware.
     * @param device Pointer to the ADC device object.
     * @return Operation status.
     */
    rt_err_t (*close)(struct rt_adc_device *device);


    /**
     * @brief Configure one ADC conversion session before data transfer.
     * @param device Pointer to the ADC device object.
     * @param channels ADC channel selection mask.
     * @return Operation status.
     */
    rt_err_t (*session_config)(struct rt_adc_device *device, rt_uint32_t channels);

#if defined(RT_ADC_USING_TRIGGER)
    /**
     * @brief Preconfigure the ADC backend trigger state for the next hardware configuration pass.
     * @param device Pointer to the ADC device object.
     * @param cfg Pointer to the active ADC trigger configuration object.
     * @return Operation status.
     * @note The implementation may only validate @p cfg, update pending driver
     *       state, or fill HAL initialization fields. It must not start the
     *       trigger source or arm ADC conversions.
     */
    rt_err_t (*trigger_prepare)(struct rt_adc_device *device, const struct rt_adc_trigger_cfg *cfg);
#endif /* defined(RT_ADC_USING_TRIGGER) */

    /**
     * @brief Handle ADC control commands.
     * @param device Pointer to the ADC device object.
     * @param cmd Control command.
     * @param args Pointer to the control argument buffer.
     * @return Operation status.
     */
    rt_err_t (*control)(struct rt_adc_device *device, int cmd, void *args);
};

/**
 * @brief ADC finite-sequence operation table.
 */
struct rt_adc_sequence_ops
{
    /**
     * @brief Start one active finite transfer session.
     * @param device Pointer to the ADC device object.
     * @param channels ADC channel selection mask.
     * @param cfg Pointer to the sequence request object.
     * @return Operation status.
     */
    rt_err_t (*start)(struct rt_adc_device *device, rt_uint32_t channels, const struct rt_adc_sequence_cfg *cfg);

    /**
     * @brief Read one converted sample from an active finite transfer session.
     * @param device Pointer to the ADC device object.
     * @param value Pointer to the output sample value.
     * @param timeout_ms Read timeout in milliseconds; negative means wait forever.
     * @return Operation status.
     */
    rt_err_t (*read)(struct rt_adc_device *device, rt_uint32_t *value, rt_int32_t timeout_ms);

    /**
     * @brief Stop one active finite transfer session.
     * @param device Pointer to the ADC device object.
     * @return Operation status.
     */
    rt_err_t (*stop)(struct rt_adc_device *device);
};

#ifdef RT_ADC_USING_STREAM
/**
 * @brief ADC stream operation table.
 */
struct rt_adc_stream_ops
{
    /**
     * @brief Start one active stream session.
     * @param device Pointer to the ADC device object.
     * @param channels ADC channel selection mask.
     * @param cfg Pointer to the stream configuration object.
     * @return Operation status.
     */
    rt_err_t (*start)(struct rt_adc_device *device, rt_uint32_t channels, const struct rt_adc_stream_cfg *cfg);

    /**
     * @brief Synchronize a backend DMA sample range before CPU access.
     * @param device Pointer to the ADC device object.
     * @param sample_buffer Pointer to the DMA sample buffer.
     * @param sample_count Number of samples to synchronize.
     * @return Operation status.
     */
    rt_err_t (*sync)(struct rt_adc_device *device, const rt_uint32_t *sample_buffer, rt_size_t sample_count);

    /**
     * @brief Stop one active stream session.
     * @param device Pointer to the ADC device object.
     * @param hardware_stopped Pointer to the hardware-stop state output.
     * @return Operation status.
     *
     * The backend sets @p hardware_stopped to RT_TRUE after the ADC hardware
     * conversion path has stopped. When this callback returns an error with
     * @p hardware_stopped set to RT_TRUE, the framework treats it as a
     * post-stop cleanup failure and moves the stream to IDLE.
     */
    rt_err_t (*stop)(struct rt_adc_device *device, rt_bool_t *hardware_stopped);
};
#endif /* RT_ADC_USING_STREAM */


/**
 * @brief ADC driver operation table.
 */
struct rt_adc_ops
{
    const struct rt_adc_core_ops *core;         /**< Core operation table. */
    const struct rt_adc_sequence_ops *sequence; /**< Sequence-session operations. */
#ifdef RT_ADC_USING_STREAM
    const struct rt_adc_stream_ops *stream;     /**< Stream-session operations. */
#endif /* RT_ADC_USING_STREAM */
};

/**
 * @brief ADC synchronous one-frame sequence request.
 */
struct rt_adc_sequence_cfg
{
    rt_uint32_t *buffer;     /**< Destination sample buffer. */
    rt_size_t buffer_length; /**< Destination buffer length in samples. */
    rt_int32_t timeout_ms;   /**< Per-sample timeout; negative means wait forever. */
};

#ifdef RT_ADC_USING_STREAM
/**
 * @brief ADC stream backend event.
 */
enum rt_adc_stream_event
{
    RT_ADC_STREAM_EVENT_DMA_HALF = 0x01U, /**< ADC stream DMA half-transfer event. */
    RT_ADC_STREAM_EVENT_DMA_DONE = 0x02U, /**< ADC stream DMA transfer-complete event. */
    RT_ADC_STREAM_EVENT_ERROR = 0x03U     /**< ADC stream backend error event. */
};

/**
 * @brief ADC stream buffering policy.
 */
enum rt_adc_stream_policy
{
#ifdef RT_ADC_STREAM_USING_LATEST
    /**
     * @brief Keep only the latest ADC rank values.
     *
     * This policy is intended for slow-changing ADC values such as battery
     * voltage, temperature, potentiometer input, resistor-divider voltage, or
     * board status monitoring. Old values may be overwritten.
     *
     * In this policy, @ref rt_adc_stream_cfg::dma_buffer_length must be exactly
     * equal to the active ADC frame length, namely the number of enabled ADC
     * ranks. The backend must expose the DMA buffer as a single latest-frame
     * layout:
     *
     * - dma_buffer[0] stores the latest value of ADC rank 1.
     * - dma_buffer[1] stores the latest value of ADC rank 2.
     * - dma_buffer[n] stores the latest value of ADC rank n + 1.
     *
     * STM32 regular scan conversion with circular DMA naturally satisfies this
     * layout when the DMA length equals the ADC rank count. Backends for other
     * platforms may also support this policy if their DMA engine writes samples
     * in scan-rank order. If a backend produces packed, interleaved,
     * descriptor-based, hardware-FIFO, or otherwise non-rank-ordered data, it
     * must either convert the data into this latest-frame layout internally or
     * reject the configuration with -RT_ENOSYS.
     *
     * @note Latest mode is a low-overhead lockless DMA-buffer view. CPU-side
     *       atomic operations, spin locks, mutexes, or read-write locks cannot
     *       prevent the DMA engine from updating memory concurrently, because
     *       DMA does not participate in CPU locking protocols. This mode only
     *       guarantees that each buffer index maps to the corresponding ADC rank
     *       latest value; it does not guarantee that the copied frame is a
     *       single hardware scan-cycle snapshot. Use RT_ADC_STREAM_POLICY_FIFO
     *       when ordered and frame-accurate samples are required.
     */
    RT_ADC_STREAM_POLICY_LATEST = 0,
#endif /* RT_ADC_STREAM_USING_LATEST */
#ifdef RT_ADC_STREAM_USING_FIFO
    /**
     * @brief Preserve ADC samples in FIFO order.
     *
     * This policy is intended for continuous and loss-sensitive sampling such
     * as waveform, current, vibration, audio-like, motor-control, or
     * control-loop data where each sample matters.
     *
     * The backend reports completed DMA blocks to the ADC framework. The
     * framework copies those blocks into a ringbuffer and wakes blocking readers
     * through a completion object.
     */
    RT_ADC_STREAM_POLICY_FIFO,
#endif /* RT_ADC_STREAM_USING_FIFO */
};

/**
 * @brief ADC stream DMA data event mode.
 */
enum rt_adc_stream_dma_event_mode
{
    RT_ADC_STREAM_DMA_EVENT_AUTO = 0,  /**< Use the default event mode for the selected stream policy. */
    RT_ADC_STREAM_DMA_EVENT_NONE,      /**< Disable DMA half/full data events; DMA error events remain enabled. */
    RT_ADC_STREAM_DMA_EVENT_FULL_ONLY, /**< Report only DMA transfer-complete data events to reduce interrupt rate. */
    RT_ADC_STREAM_DMA_EVENT_HALF_FULL  /**< Report both DMA half-transfer and transfer-complete data events. */
};

/**
 * @brief ADC stream FIFO data callback type.
 * @param device Pointer to the ADC device object.
 * @param sample_count Number of newly accepted samples.
 * @param user_data Pointer to the user context.
 * @note This callback is invoked from ADC stream ISR context. It must not
 *       block, sleep, or call APIs that may suspend the current context.
 */
typedef void (*rt_adc_stream_callback_t)(struct rt_adc_device *device, rt_size_t sample_count, void *user_data);

/**
 * @brief ADC stream configuration.
 * @note The DMA buffer belongs to the caller and must remain valid until
 *       rt_adc_stream_stop() returns. The stream configuration object only
 *       needs to remain valid for the duration of rt_adc_stream_start(). A
 *       backend may use an internal cache-aligned DMA buffer when the caller
 *       buffer is not safe for platform cache maintenance. Backend drivers must
 *       copy scalar configuration fields they need after rt_adc_stream_start()
 *       returns.
 */
struct rt_adc_stream_cfg
{
    enum rt_adc_stream_policy policy;                  /**< Stream buffering policy. */
    enum rt_adc_stream_dma_event_mode dma_event_mode;  /**< DMA half/full data event mode. */

    /**
     * @brief DMA circular staging buffer.
     *
     * For RT_ADC_STREAM_POLICY_LATEST, this buffer stores exactly one latest
     * ADC scan frame. dma_buffer_length must equal the active frame length.
     * Each element maps to one configured ADC rank.
     *
     * For RT_ADC_STREAM_POLICY_FIFO, this buffer is a DMA staging buffer. The
     * default rt_adc_stream_start() entry validates only basic buffer presence
     * and capacity. It does not require each DMA data-event block to end on an
     * ADC scan-frame boundary.
     *
     * Use rt_adc_stream_start_frame_aligned_fifo() when continuous FIFO sampling
     * requires a strict frame-aligned DMA/FIFO layout before the stream starts.
     */
    rt_uint32_t *dma_buffer;

    /**
     * @brief DMA buffer length in samples.
     */
    rt_size_t dma_buffer_length;
#ifdef RT_ADC_STREAM_USING_FIFO
    rt_uint32_t *fifo_buffer;                          /**< FIFO storage for FIFO policy. */
    rt_size_t fifo_buffer_length;                      /**< FIFO buffer length in samples. */
    rt_size_t watermark;                               /**< FIFO wakeup or callback threshold in samples. */
    rt_adc_stream_callback_t callback;                 /**< Optional ISR-context FIFO data callback. */
    void *user_data;                                   /**< User data passed to the FIFO data callback. */
#endif /* RT_ADC_STREAM_USING_FIFO */
};

/**
 * @brief ADC stream runtime control block owned by the ADC framework.
 */
struct rt_adc_stream_ctrl
{
    rt_bool_t active;                                /**< Whether a stream backend session is active. */
    enum rt_adc_stream_policy policy;                 /**< Active stream buffering policy. */
    enum rt_adc_stream_dma_event_mode dma_event_mode; /**< Active DMA data event mode. */
    rt_uint32_t *dma_buffer;                          /**< DMA circular staging buffer. */
    rt_size_t dma_buffer_length;                      /**< DMA buffer length in samples. */
    rt_size_t frame_length;                           /**< Samples in one ADC scan frame. */
#ifdef RT_ADC_STREAM_USING_FIFO
    struct rt_ringbuffer fifo;                        /**< FIFO storage for FIFO policy. */
    rt_bool_t fifo_enabled;                           /**< FIFO initialized flag. */
    /**
     * @brief Reader wake completion for FIFO stream.
     *
     * The FIFO ringbuffer is the source of truth for available data. This
     * completion object is only a wakeup edge for blocking reads.
     */
    struct rt_completion rx_cpt;
    rt_size_t overflow_count;                         /**< FIFO overrun count. */
    rt_size_t watermark;                              /**< FIFO wakeup or callback threshold. */
    rt_adc_stream_callback_t callback;                /**< Optional FIFO data callback. */
    void *user_data;                                  /**< Callback private data. */
#endif /* RT_ADC_STREAM_USING_FIFO */
    rt_atomic_t last_error;                           /**< Atomic last stream backend error. */
};
#endif /* RT_ADC_USING_STREAM */

/**
 * @brief ADC active session runtime control block.
 */
struct rt_adc_session_ctrl
{
    rt_uint32_t channels;    /**< Cached active ADC channel selection mask. */
    rt_size_t channel_count; /**< Cached active session channel count. */
    rt_bool_t configured;    /**< Whether the cached session configuration is valid. */
};

/**
 * @brief ADC device object.
 */
struct rt_adc_device
{
    struct rt_device parent;                 /**< RT-Thread device object. */
    const struct rt_adc_ops *ops;            /**< ADC driver operation table. */
    rt_atomic_t state;                       /**< Atomic ADC runtime state. */
    struct rt_spinlock spinlock;             /**< Protects ADC stream FIFO shared by thread context and ISR. */
    rt_uint32_t default_vref_mv;             /**< Default reference voltage in millivolts. */
    struct rt_adc_session_ctrl session_ctrl; /**< ADC active session control block. */
#if defined(RT_ADC_USING_TRIGGER)
    struct rt_adc_trigger_ctrl trigger_ctrl; /**< ADC trigger runtime control block. */
#endif /* defined(RT_ADC_USING_TRIGGER) */
#ifdef RT_ADC_USING_STREAM
    struct rt_adc_stream_ctrl stream_ctrl;   /**< ADC stream runtime control block. */
#endif /* RT_ADC_USING_STREAM */
};

/**
 * @brief Count selected ADC channels in one channel mask.
 * @param channels ADC channel selection mask.
 * @return Number of selected channels.
 */
rt_inline rt_size_t rt_adc_channel_mask_count(rt_uint32_t channels)
{
#if defined(__GNUC__) || defined(__clang__)
    return (rt_size_t)__builtin_popcount((unsigned int)channels);
#else
    rt_size_t count;

    count = 0U;
    while (channels != 0U)
    {
        channels &= channels - 1U;
        count++;
    }

    return count;
#endif /* defined(__GNUC__) || defined(__clang__) */
}

/**
 * @brief Take the lowest selected ADC channel from one channel mask.
 * @param channels Pointer to the ADC channel selection mask.
 * @return Selected channel index, or 0xff if the mask is empty.
 */
rt_inline rt_uint8_t rt_adc_channel_mask_take_lsb(rt_uint32_t *channels)
{
    rt_uint8_t bit;

    if ((channels == RT_NULL) || (*channels == 0U))
    {
        return 0xffU;
    }

#if defined(__GNUC__) || defined(__clang__)
    bit = (rt_uint8_t)__builtin_ctz((unsigned int)*channels);
#else
    for (bit = 0U; bit < 32U; bit++)
    {
        if ((*channels & RT_ADC_CHANNEL_MASK(bit)) != 0U)
        {
            break;
        }
    }
#endif /* defined(__GNUC__) || defined(__clang__) */

    *channels &= ~RT_ADC_CHANNEL_MASK(bit);
    return bit;
}

/**
 * @brief Register an ADC device with the RT-Thread device framework.
 * @param device Pointer to the ADC device object.
 * @param name Pointer to the ADC device name string.
 * @param ops Pointer to the ADC driver operation table.
 * @param user_data Pointer to driver private data.
 * @return Operation status.
 */
rt_err_t rt_hw_adc_register(rt_adc_device_t device, const char *name, const struct rt_adc_ops *ops, const void *user_data);

/**
 * @brief Get the raw sample index of one channel in an ADC session mask.
 * @param session_channels Configured ADC session channel mask.
 * @param channel Single-channel mask to locate.
 * @param index Pointer to the output raw sample index.
 * @return Operation status.
 */
rt_err_t rt_adc_session_channel_index(rt_uint32_t session_channels, rt_uint32_t channel, rt_size_t *index);


/**
 * @brief Read one ADC conversion sequence frame.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the ADC sequence request object.
 * @param read_count Pointer to the stored sample count.
 * @return Operation status.
 */
rt_err_t rt_adc_read_sequence(rt_adc_device_t device, rt_uint32_t channels,
                              const struct rt_adc_sequence_cfg *cfg, rt_size_t *read_count);

#ifdef RT_ADC_USING_STREAM
/**
 * @brief Start one ADC stream session.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the ADC stream configuration object.
 * @return Operation status.
 */
rt_err_t rt_adc_stream_start(rt_adc_device_t device, rt_uint32_t channels, const struct rt_adc_stream_cfg *cfg);

#ifdef RT_ADC_STREAM_USING_FIFO
/**
 * @brief Start one FIFO ADC stream with strict frame-aligned buffer layout.
 * @param device Pointer to the ADC device object.
 * @param channels ADC channel selection mask.
 * @param cfg Pointer to the ADC stream configuration object.
 * @return Operation status.
 */
rt_err_t rt_adc_stream_start_frame_aligned_fifo(rt_adc_device_t device, rt_uint32_t channels, const struct rt_adc_stream_cfg *cfg);
#endif /* RT_ADC_STREAM_USING_FIFO */

/**
 * @brief Read converted samples from an active ADC stream session.
 * @param device Pointer to the ADC device object.
 * @param buffer Pointer to the destination sample buffer.
 * @param sample_count Number of samples to read.
 * @param timeout_ms Read timeout in milliseconds; negative means wait forever.
 * @return Number of samples read, or a negative RT-Thread error code.
 */
rt_ssize_t rt_adc_stream_read(rt_adc_device_t device, rt_uint32_t *buffer, rt_size_t sample_count, rt_int32_t timeout_ms);

/**
 * @brief Cancel a blocked ADC stream reader before stream shutdown.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
rt_err_t rt_adc_stream_cancel(rt_adc_device_t device);

/**
 * @brief Stop one ADC stream session.
 * @param device Pointer to the ADC device object.
 * @return Operation status.
 */
rt_err_t rt_adc_stream_stop(rt_adc_device_t device);

/**
 * @brief Notify the ADC framework of one stream backend event.
 * @param device Pointer to the ADC device object.
 * @param event ADC stream event reported by the backend or ISR.
 * @param sample_buffer Pointer to the completed sample buffer block.
 * @param sample_count Number of samples in @p sample_buffer.
 * @return Operation status.
 */
rt_err_t rt_hw_adc_stream_isr(rt_adc_device_t device, enum rt_adc_stream_event event,
                               const rt_uint32_t *sample_buffer, rt_size_t sample_count);
#endif /* RT_ADC_USING_STREAM */

/**
 * @brief Convert one raw ADC sample to millivolts.
 * @param raw_value Raw ADC sample value.
 * @param vref_mv ADC reference voltage in millivolts.
 * @param resolution_bits ADC resolution in bits.
 * @param voltage_mv Pointer to the output voltage in millivolts.
 * @return Operation status.
 */
rt_err_t rt_adc_raw_to_voltage_mv(rt_uint32_t raw_value, rt_uint32_t vref_mv, rt_uint8_t resolution_bits, rt_uint32_t *voltage_mv);

/**
 * @brief Convert one ADC raw sample to a scaled voltage in millivolts.
 * @param raw_value Raw ADC sample code.
 * @param vref_mv ADC reference voltage in millivolts.
 * @param resolution_bits ADC resolution in bits.
 * @param scale_num Voltage scaling numerator.
 * @param scale_den Voltage scaling denominator.
 * @param voltage_mv Pointer to the output scaled voltage in millivolts.
 * @return Operation status.
 *
 * The scaled voltage is calculated as:
 *
 *     raw_to_voltage_mv(raw_value) * scale_num / scale_den
 *
 * @note @p scale_num and @p scale_den may describe any positive rational
 *       scaling ratio that does not overflow the internal calculation. The
 *       final scaled millivolt value must fit in rt_uint32_t.
 *
 * @retval RT_EOK The conversion completed successfully.
 * @retval -RT_EINVAL A pointer is null, a scale argument is zero, the ADC
 *         conversion arguments are invalid, or the scaled result overflows
 *         rt_uint32_t.
 */
rt_err_t rt_adc_raw_to_scaled_voltage_mv(rt_uint32_t raw_value, rt_uint32_t vref_mv, rt_uint8_t resolution_bits, rt_uint32_t scale_num, rt_uint32_t scale_den, rt_uint32_t *voltage_mv);

/**
 * @brief Read ADC samples and convert them to millivolts.
 * @param device Pointer to the ADC device object.
 * @param voltages_mv Pointer to the output voltage buffer in millivolts.
 * @param size Output voltage buffer length.
 * @param timeout_ms Per-sample timeout in milliseconds; negative means wait forever.
 * @return Operation status.
 *
 * @note This API reads the currently configured ADC session and does not modify
 *       the active channel mask. If default_vref_mv is zero, callers that need
 *       backend-calculated VDDA must include the backend VREF channel in the
 *       configured session. The VREF sample is used only as the reference for
 *       conversion and is not auto-inserted by this API.
 */
rt_err_t rt_adc_voltage(rt_adc_device_t device, rt_uint32_t *voltages_mv, rt_size_t size, rt_int32_t timeout_ms);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ADC_V2_H__ */
