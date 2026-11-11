/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-09     wdfk-prog    split adc v2 msh command implementation
 */

/**
 * @file adc_v2_msh.c
 * @brief ADC V2 FinSH/MSH command implementation.
 */

#include <rtconfig.h>

#if defined(RT_USING_ADC_V2) && defined(RT_USING_FINSH) && defined(RT_ADC_V2_USING_MSH)

#include <stdlib.h>

#include <rtdevice.h>
#include <rtthread.h>
#include <finsh.h>

#include <drivers/adc_v2.h>

/** @brief Default FinSH temporary read buffer capacity in samples. */
#define RT_ADC_MSH_VALUE_BUFFER_SIZE 32U

/** @brief Default timeout in milliseconds for ADC MSH sequence read command. */
#define RT_ADC_MSH_SEQ_DEFAULT_TIMEOUT_MS 1000

/** @brief Default FinSH stream read timeout in milliseconds. */
#define RT_ADC_MSH_STREAM_READ_TIMEOUT_MS 1000

/** @brief Default FinSH stream DMA buffer capacity in samples. */
#define RT_ADC_MSH_STREAM_DMA_BUFFER_SIZE 32U

/** @brief Default FIFO storage capacity in samples for the ADC MSH FIFO stream test. */
#define RT_ADC_MSH_FIFO_TEST_FIFO_BUFFER_SIZE 512U

/**
 * @brief Print backend-specific ADC FinSH command usage.
 */
rt_weak void rt_adc_msh_special_help(void)
{
}

/**
 * @brief Handle backend-specific ADC FinSH commands.
 * @param device Pointer to the selected ADC device object.
 * @param argc Argument count excluding the top-level adc command.
 * @param argv Argument vector excluding the top-level adc command.
 * @return Operation status.
 */
rt_weak rt_err_t rt_adc_msh_special(rt_adc_device_t device, int argc, char **argv)
{
    RT_UNUSED(device);
    RT_UNUSED(argc);
    RT_UNUSED(argv);

    return -RT_ENOSYS;
}

#if defined(RT_ADC_USING_TRIGGER)
/**
 * @brief Print ADC trigger MSH command usage.
 */
static void adc_msh_usage_trigger(void)
{
#if defined(RT_ADC_TRIGGER_USING_TIMER)
    rt_kprintf("  adc trigger set timer_update <timer_device> <freq_hz>\n");
    rt_kprintf("  adc trigger set timer_compare <timer_device> <timer_ch> <freq_hz>\n");
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) */
#if defined(RT_ADC_TRIGGER_USING_COMPARE)
    rt_kprintf("  adc trigger set compare [comparator_device] <num> <rising|falling|both>, num: 0~31\n");
#endif /* defined(RT_ADC_TRIGGER_USING_COMPARE) */
    rt_kprintf("  adc trigger clear\n");
    rt_kprintf("  adc trigger status\n");
}
#endif /* defined(RT_ADC_USING_TRIGGER) */

#if defined(RT_ADC_USING_STREAM)
/**
 * @brief Print ADC stream MSH command usage.
 */
static void adc_msh_usage_stream(void)
{
    rt_kprintf("  adc stream start <num0> [num1 ...], num: 0~31\n");
    rt_kprintf("  adc stream read [timeout_ms]\n");
    rt_kprintf("  adc stream cancel\n");
    rt_kprintf("  adc stream stop\n");
#if defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO)
    rt_kprintf("  adc fifo <timeout_ms> <num0> [num1 ...]\n");
#endif /* defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO) */
}
#endif /* defined(RT_ADC_USING_STREAM) */

/**
 * @brief Print ADC FinSH command usage.
 */
static void adc_msh_usage(void)
{
    rt_kprintf("Usage:\n");
    rt_kprintf("  adc probe <device>\n");
    rt_kprintf("  adc close\n");
    rt_kprintf("  adc config <num0> [num1 ...], num: 0~31, eg: 0 1 10\n");
    rt_kprintf("  adc read\n");
    rt_kprintf("  adc voltage <timeout_ms>\n");
    rt_kprintf("    voltage reads the current session configured by adc config\n");
    rt_kprintf("    if default_vref is absent, adc config must include the backend VREF channel\n");
    rt_kprintf("  adc seq <timeout_ms> <num0> [num1 ...], num: 0~31, eg: 0 1 10\n");
#if defined(RT_ADC_USING_TRIGGER)
    adc_msh_usage_trigger();
#endif /* defined(RT_ADC_USING_TRIGGER) */

#if defined(RT_ADC_USING_STREAM)
    adc_msh_usage_stream();
#endif /* defined(RT_ADC_USING_STREAM) */

    rt_adc_msh_special_help();
}

/**
 * @brief Convert one shell argument to a single-channel mask.
 * @param arg Pointer to the shell argument string.
 * @param channels Pointer to the output channel mask.
 * @return Operation status.
 */
static rt_err_t adc_msh_parse_channel_mask(const char *arg, rt_uint32_t *channels)
{
    char *endptr;
    unsigned long value;

    if ((*arg == '\0') || (*arg == '-'))
    {
        return -RT_EINVAL;
    }

    endptr = RT_NULL;
    value = strtoul(arg, &endptr, 0);
    if ((endptr == arg) || (endptr == RT_NULL) || (*endptr != '\0') || (value >= 32UL))
    {
        return -RT_EINVAL;
    }

    *channels = RT_ADC_CHANNEL_MASK(value);
    return RT_EOK;
}

/**
 * @brief Convert one shell argument to a timeout value.
 * @param arg Pointer to the shell argument string.
 * @return Timeout in milliseconds; negative means wait forever.
 *
 * @note This command keeps the permissive MSH parsing convention: strtol()
 *       is used without endptr validation, so a non-numeric string with no
 *       converted digits is treated as 0 by the C library conversion path. A
 *       timeout value of 0 means non-blocking/immediate timeout.
 */
static rt_int32_t adc_msh_parse_timeout(const char *arg)
{
    return (rt_int32_t)strtol(arg, RT_NULL, 0);
}

#if defined(RT_ADC_USING_TRIGGER) && (defined(RT_ADC_TRIGGER_USING_TIMER) || defined(RT_ADC_TRIGGER_USING_COMPARE))
/**
 * @brief Convert one shell argument to an unsigned integer.
 * @param arg Pointer to the shell argument string.
 * @param max_value Maximum accepted value.
 * @param value Pointer to the output value.
 * @return Operation status.
 */
static rt_err_t adc_msh_parse_ulong(const char *arg, unsigned long max_value, unsigned long *value)
{
    char *endptr;
    unsigned long parsed;

    if ((arg == RT_NULL) || (value == RT_NULL) || (*arg == '\0') || (*arg == '-'))
    {
        return -RT_EINVAL;
    }

    endptr = RT_NULL;
    parsed = strtoul(arg, &endptr, 0);
    if ((endptr == arg) || (endptr == RT_NULL) || (*endptr != '\0') || (parsed > max_value))
    {
        return -RT_EINVAL;
    }

    *value = parsed;
    return RT_EOK;
}

#if defined(RT_ADC_TRIGGER_USING_COMPARE)
/**
 * @brief Convert one shell argument to an ADC trigger edge selector.
 * @param arg Pointer to the shell argument string.
 * @param edge Pointer to the output trigger edge selector.
 * @return Operation status.
 */
static rt_err_t adc_msh_parse_trigger_edge(const char *arg, enum rt_adc_trigger_edge *edge)
{
    if ((arg == RT_NULL) || (edge == RT_NULL))
    {
        return -RT_EINVAL;
    }

    if (!rt_strcmp(arg, "rising"))
    {
        *edge = RT_ADC_TRIGGER_EDGE_RISING;
        return RT_EOK;
    }

    if (!rt_strcmp(arg, "falling"))
    {
        *edge = RT_ADC_TRIGGER_EDGE_FALLING;
        return RT_EOK;
    }

    if (!rt_strcmp(arg, "both"))
    {
        *edge = RT_ADC_TRIGGER_EDGE_BOTH;
        return RT_EOK;
    }

    return -RT_EINVAL;
}

#endif /* defined(RT_ADC_TRIGGER_USING_COMPARE) */

/**
 * @brief Find one trigger source device by shell argument.
 * @param name Pointer to the source device name string.
 * @param source Pointer to the output source device object.
 * @return Operation status.
 */
static rt_err_t adc_msh_find_trigger_source(const char *name, rt_device_t *source)
{
    rt_device_t dev;

    if ((name == RT_NULL) || (source == RT_NULL))
    {
        return -RT_EINVAL;
    }

    dev = rt_device_find(name);
    if (dev == RT_NULL)
    {
        rt_kprintf("trigger source %s not found\n", name);
        return -RT_ERROR;
    }

    *source = dev;
    return RT_EOK;
}
#endif /* defined(RT_ADC_USING_TRIGGER) && (defined(RT_ADC_TRIGGER_USING_TIMER) || defined(RT_ADC_TRIGGER_USING_COMPARE)) */

#ifdef RT_ADC_USING_STREAM
/**
 * @brief Clear the FinSH stream scratch buffer owner.
 * @param stream_device Pointer to the saved stream device owner.
 */
static void adc_msh_clear_stream_owner(rt_adc_device_t *stream_device)
{
    if (stream_device != RT_NULL)
    {
        *stream_device = RT_NULL;
    }
}

/**
 * @brief Get the current ADC framework state for the FinSH command.
 * @param device Pointer to the ADC device object.
 * @return Current ADC runtime state.
 */
static enum rt_adc_state adc_msh_get_state(rt_adc_device_t device)
{
    return (enum rt_adc_state)rt_atomic_load(&device->state);
}

/**
 * @brief Check whether the FinSH stream scratch buffer is still owned by an active stream.
 * @param stream_device Saved stream device owner.
 * @return RT_TRUE if the stream buffer is still owned by an active stream.
 */
static rt_bool_t adc_msh_stream_buffer_is_active(rt_adc_device_t stream_device)
{
    if (stream_device == RT_NULL)
    {
        return RT_FALSE;
    }

    return (adc_msh_get_state(stream_device) == RT_ADC_STATE_STREAM) ? RT_TRUE : RT_FALSE;
}
#endif /* RT_ADC_USING_STREAM */

static rt_adc_device_t device = RT_NULL;
#ifdef RT_ADC_USING_STREAM
static rt_adc_device_t stream_device = RT_NULL;
static rt_uint32_t stream_dma_buffer[RT_ADC_MSH_STREAM_DMA_BUFFER_SIZE];
#if defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO)
static rt_uint32_t stream_fifo_buffer[RT_ADC_MSH_FIFO_TEST_FIFO_BUFFER_SIZE];
#endif /* defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO) */
#endif /* RT_ADC_USING_STREAM */


#if defined(RT_ADC_USING_TRIGGER)
/**
 * @brief Handle ADC trigger subcommands.
 * @param device Pointer to the selected ADC device object.
 * @param argc Argument count excluding "adc trigger".
 * @param argv Argument vector excluding "adc trigger".
 * @return Command status.
 */
static rt_err_t adc_msh_trigger(rt_adc_device_t device, int argc, char **argv)
{
    rt_err_t result;

    if (argc < 1)
    {
        adc_msh_usage();
        return -RT_EINVAL;
    }

    if (!rt_strcmp(argv[0], "clear"))
    {
        if (argc != 1)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        result = rt_adc_trigger_clear(device);
        if (result == RT_EOK)
        {
            rt_kprintf("adc trigger cleared\n");
        }
        return result;
    }

    if (!rt_strcmp(argv[0], "status"))
    {
        if (argc != 1)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        rt_kprintf("adc trigger: %s\n", rt_adc_trigger_is_set(device) == RT_TRUE ? "set" : "clear");
        return RT_EOK;
    }

    if (!rt_strcmp(argv[0], "set"))
    {
        struct rt_adc_trigger_cfg trigger_cfg;

        if (argc < 2)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        rt_memset(&trigger_cfg, 0, sizeof(trigger_cfg));
#if defined(RT_ADC_TRIGGER_USING_TIMER)
        if (!rt_strcmp(argv[1], "timer_update"))
        {
            unsigned long freq_hz;

            if (argc != 4)
            {
                adc_msh_usage();
                return -RT_EINVAL;
            }

            result = adc_msh_find_trigger_source(argv[2], &trigger_cfg.event.timer.timer);
            if (result != RT_EOK)
            {
                return result;
            }

            result = adc_msh_parse_ulong(argv[3], 0xffffffffUL, &freq_hz);
            if ((result != RT_EOK) || (freq_hz == 0UL))
            {
                rt_kprintf("invalid adc trigger timer frequency: %s\n", argv[3]);
                return (result != RT_EOK) ? result : -RT_EINVAL;
            }

            trigger_cfg.type = RT_ADC_TRIGGER_TIMER_UPDATE;
            trigger_cfg.event.timer.freq_hz = (rt_uint32_t)freq_hz;
            trigger_cfg.event.timer.channel = 0U;
        }
        else if (!rt_strcmp(argv[1], "timer_compare"))
        {
            unsigned long channel;
            unsigned long freq_hz;

            if (argc != 5)
            {
                adc_msh_usage();
                return -RT_EINVAL;
            }

            result = adc_msh_find_trigger_source(argv[2], &trigger_cfg.event.timer.timer);
            if (result != RT_EOK)
            {
                return result;
            }

            result = adc_msh_parse_ulong(argv[3], 65535UL, &channel);
            if ((result != RT_EOK) || (channel == 0UL))
            {
                rt_kprintf("invalid adc trigger timer channel: %s\n", argv[3]);
                return (result != RT_EOK) ? result : -RT_EINVAL;
            }

            result = adc_msh_parse_ulong(argv[4], 0xffffffffUL, &freq_hz);
            if ((result != RT_EOK) || (freq_hz == 0UL))
            {
                rt_kprintf("invalid adc trigger timer frequency: %s\n", argv[4]);
                return (result != RT_EOK) ? result : -RT_EINVAL;
            }

            trigger_cfg.type = RT_ADC_TRIGGER_TIMER_COMPARE;
            trigger_cfg.event.timer.freq_hz = (rt_uint32_t)freq_hz;
            trigger_cfg.event.timer.channel = (rt_uint16_t)channel;
        }
        else
#endif /* defined(RT_ADC_TRIGGER_USING_TIMER) */
#if defined(RT_ADC_TRIGGER_USING_COMPARE)
            if (!rt_strcmp(argv[1], "compare"))
        {
            unsigned long channel;
            int channel_arg;
            int edge_arg;

            if ((argc != 4) && (argc != 5))
            {
                adc_msh_usage();
                return -RT_EINVAL;
            }

            if (argc == 5)
            {
                result = adc_msh_find_trigger_source(argv[2], &trigger_cfg.event.compare.comparator);
                if (result != RT_EOK)
                {
                    return result;
                }
                channel_arg = 3;
                edge_arg = 4;
            }
            else
            {
                channel_arg = 2;
                edge_arg = 3;
            }

            result = adc_msh_parse_ulong(argv[channel_arg], 65535UL, &channel);
            if ((result != RT_EOK) || (channel == 0UL))
            {
                rt_kprintf("invalid adc trigger compare channel: %s\n", argv[channel_arg]);
                return (result != RT_EOK) ? result : -RT_EINVAL;
            }

            result = adc_msh_parse_trigger_edge(argv[edge_arg], &trigger_cfg.event.compare.edge);
            if (result != RT_EOK)
            {
                rt_kprintf("invalid adc trigger edge: %s\n", argv[edge_arg]);
                return result;
            }

            trigger_cfg.type = RT_ADC_TRIGGER_ANALOG_COMPARE;
            trigger_cfg.event.compare.channel = (rt_uint16_t)channel;
        }
        else
#endif /* defined(RT_ADC_TRIGGER_USING_COMPARE) */
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        result = rt_adc_trigger_set(device, &trigger_cfg);
        if (result == RT_EOK)
        {
            rt_kprintf("adc trigger set: %s\n", argv[1]);
        }
        return result;
    }

    adc_msh_usage();
    return -RT_EINVAL;
}
#endif /* defined(RT_ADC_USING_TRIGGER) */

#ifdef RT_ADC_USING_STREAM
/**
 * @brief Handle ADC stream subcommands.
 * @param device Pointer to the selected ADC device object.
 * @param argc Argument count excluding "adc stream".
 * @param argv Argument vector excluding "adc stream".
 * @return Command status.
 */
static rt_err_t adc_msh_stream(rt_adc_device_t device, int argc, char **argv)
{
    rt_uint32_t values[RT_ADC_MSH_VALUE_BUFFER_SIZE];
    rt_size_t count;
    rt_size_t index;
    rt_err_t result;

    if (argc < 1)
    {
        adc_msh_usage();
        return -RT_EINVAL;
    }

    if (!rt_strcmp(argv[0], "start"))
    {
#ifndef RT_ADC_STREAM_USING_LATEST
        return -RT_ENOSYS;
#else
        struct rt_adc_stream_cfg stream_cfg;
        rt_uint32_t channels;
        rt_uint32_t channel_mask;

        if (argc < 2)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        if (adc_msh_get_state(device) == RT_ADC_STATE_STREAM)
        {
            rt_kprintf("adc stream is already running, stop it first\n");
            return -RT_EBUSY;
        }

        channels = 0U;
        for (index = 0U; index < (rt_size_t)(argc - 1); index++)
        {
            result = adc_msh_parse_channel_mask(argv[index + 1], &channel_mask);
            if (result != RT_EOK)
            {
                rt_kprintf("invalid adc channel: %s\n", argv[index + 1]);
                return result;
            }
            channels |= channel_mask;
        }

        count = rt_adc_channel_mask_count(channels);
        if (count == 0U)
        {
            return -RT_EINVAL;
        }

        if (adc_msh_stream_buffer_is_active(stream_device) == RT_TRUE)
        {
            rt_kprintf("adc stream is already running, stop it first\n");
            return -RT_EBUSY;
        }
        adc_msh_clear_stream_owner(&stream_device);

        if (count > RT_ADC_MSH_STREAM_DMA_BUFFER_SIZE)
        {
            rt_kprintf("adc stream buffer too large, max %u samples\n", (unsigned int)RT_ADC_MSH_STREAM_DMA_BUFFER_SIZE);
            return -RT_EINVAL;
        }

        rt_memset(&stream_cfg, 0, sizeof(stream_cfg));
        stream_cfg.policy = RT_ADC_STREAM_POLICY_LATEST;
        stream_cfg.dma_event_mode = RT_ADC_STREAM_DMA_EVENT_AUTO;
        stream_cfg.dma_buffer = stream_dma_buffer;
        stream_cfg.dma_buffer_length = count;

        result = rt_adc_stream_start(device, channels, &stream_cfg);
        if (result == RT_EOK)
        {
            stream_device = device;
        }
        else if (adc_msh_get_state(device) == RT_ADC_STATE_STREAM)
        {
            stream_device = device;
            rt_kprintf("adc stream start failed but stream hardware may still be running, stop it first\n");
        }
        else
        {
            adc_msh_clear_stream_owner(&stream_device);
        }
        return result;
#endif /* RT_ADC_STREAM_USING_LATEST */
    }

    if (!rt_strcmp(argv[0], "read"))
    {
        rt_ssize_t read_count;
        rt_int32_t timeout_ms;

        if (argc > 2)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        if ((stream_device != RT_NULL) && (stream_device != device))
        {
            rt_kprintf("adc stream belongs to another device\n");
            return -RT_EBUSY;
        }

        if (adc_msh_get_state(device) != RT_ADC_STATE_STREAM)
        {
            rt_kprintf("adc stream is not running\n");
            return -RT_EINVAL;
        }

        count = device->stream_ctrl.frame_length;
        if (count == 0U)
        {
            rt_kprintf("adc stream channel count is zero\n");
            return -RT_EINVAL;
        }

        if (count > RT_ADC_MSH_VALUE_BUFFER_SIZE)
        {
            rt_kprintf("adc stream read count too large, max %u samples\n", (unsigned int)RT_ADC_MSH_VALUE_BUFFER_SIZE);
            return -RT_EINVAL;
        }

        timeout_ms = (argc == 2) ? adc_msh_parse_timeout(argv[1]) : RT_ADC_MSH_STREAM_READ_TIMEOUT_MS;
        read_count = rt_adc_stream_read(device, values, count, timeout_ms);
        if (read_count > 0)
        {
            for (index = 0U; index < (rt_size_t)read_count; index++)
            {
                rt_kprintf("[%u]=%lu\n", (unsigned int)index, (unsigned long)values[index]);
            }
        }

        return (read_count >= 0) ? RT_EOK : (rt_err_t)read_count;
    }

    if (!rt_strcmp(argv[0], "stop"))
    {
        if (argc != 1)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        if ((stream_device != RT_NULL) && (stream_device != device))
        {
            rt_kprintf("adc stream belongs to another device\n");
            return -RT_EBUSY;
        }

        result = rt_adc_stream_stop(device);
        if (result == RT_EOK)
        {
            adc_msh_clear_stream_owner(&stream_device);
        }
        return result;
    }

    if (!rt_strcmp(argv[0], "cancel"))
    {
        if (argc != 1)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        if ((stream_device != RT_NULL) && (stream_device != device))
        {
            rt_kprintf("adc stream belongs to another device\n");
            return -RT_EBUSY;
        }

        return rt_adc_stream_cancel(device);
    }

    adc_msh_usage();
    return -RT_EINVAL;
}
#endif /* RT_ADC_USING_STREAM */

#if defined(RT_ADC_USING_STREAM) && defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO)
#define RT_ADC_MSH_FIFO_TEST_READ_FRAME_COUNT 16U
#define RT_ADC_MSH_FIFO_TEST_READ_TIMEOUT_MS  1000
/**
 * @brief Handle the ADC FIFO stream test command.
 * @param device Pointer to the selected ADC device object.
 * @param argc Argument count excluding "adc fifo".
 * @param argv Argument vector excluding "adc fifo".
 * @return Command status.
 */
static rt_err_t adc_msh_fifo_test(rt_adc_device_t device, int argc, char **argv)
{
    struct rt_adc_stream_cfg stream_cfg;
    rt_uint32_t *buffer;
    rt_uint32_t channels;
    rt_uint32_t channel_mask;
    rt_size_t channel_count;
    rt_size_t sample_count;
    rt_size_t dma_buffer_length;
    rt_size_t fifo_buffer_length;
    rt_size_t read_times;
    rt_size_t index;
    rt_size_t full_count;
    rt_size_t partial_count;
    rt_size_t timeout_count;
    rt_size_t error_count;
    rt_size_t total_samples;
    rt_tick_t begin_tick;
    rt_tick_t end_tick;
    rt_tick_t timeout_tick;
    rt_int32_t timeout_ms;
    rt_err_t result;
    rt_err_t stop_result;

    if (argc < 2)
    {
        adc_msh_usage();
        return -RT_EINVAL;
    }

    timeout_ms = adc_msh_parse_timeout(argv[0]);
    if (timeout_ms <= 0)
    {
        rt_kprintf("fifo test timeout_ms must be greater than 0\n");
        return -RT_EINVAL;
    }

    if (adc_msh_get_state(device) == RT_ADC_STATE_STREAM)
    {
        rt_kprintf("adc stream is already running, stop it first\n");
        return -RT_EBUSY;
    }

    if (adc_msh_stream_buffer_is_active(stream_device) == RT_TRUE)
    {
        rt_kprintf("adc stream is already running, stop it first\n");
        return -RT_EBUSY;
    }
    adc_msh_clear_stream_owner(&stream_device);

    channels = 0U;
    for (index = 0U; index < (rt_size_t)(argc - 1); index++)
    {
        result = adc_msh_parse_channel_mask(argv[index + 1], &channel_mask);
        if (result != RT_EOK)
        {
            rt_kprintf("invalid adc channel: %s\n", argv[index + 1]);
            return result;
        }
        channels |= channel_mask;
    }

    channel_count = rt_adc_channel_mask_count(channels);
    if (channel_count == 0U)
    {
        return -RT_EINVAL;
    }

    if (RT_ADC_MSH_STREAM_DMA_BUFFER_SIZE < (channel_count * 2U))
    {
        rt_kprintf("adc fifo test dma buffer too small, min %u samples\n", (unsigned int)(channel_count * 2U));
        return -RT_EINVAL;
    }

    sample_count = channel_count * RT_ADC_MSH_FIFO_TEST_READ_FRAME_COUNT;
    if ((sample_count == 0U) || (sample_count > (((rt_size_t)-1) / sizeof(rt_uint32_t))))
    {
        rt_kprintf("adc fifo test read sample count is too large\n");
        return -RT_EINVAL;
    }

    dma_buffer_length = (RT_ADC_MSH_STREAM_DMA_BUFFER_SIZE / (channel_count * 2U)) * (channel_count * 2U);
    fifo_buffer_length = (RT_ADC_MSH_FIFO_TEST_FIFO_BUFFER_SIZE / channel_count) * channel_count;
    if (fifo_buffer_length < (dma_buffer_length / 2U))
    {
        rt_kprintf("adc fifo test fifo buffer too small, min %u samples\n", (unsigned int)(dma_buffer_length / 2U));
        return -RT_EINVAL;
    }

    buffer = (rt_uint32_t *)rt_malloc(sample_count * sizeof(rt_uint32_t));
    if (buffer == RT_NULL)
    {
        rt_kprintf("no memory for fifo test buffer\n");
        return -RT_ENOMEM;
    }

    rt_memset(&stream_cfg, 0, sizeof(stream_cfg));
    stream_cfg.policy = RT_ADC_STREAM_POLICY_FIFO;
    stream_cfg.dma_event_mode = RT_ADC_STREAM_DMA_EVENT_HALF_FULL;
    stream_cfg.dma_buffer = stream_dma_buffer;
    stream_cfg.dma_buffer_length = dma_buffer_length;
    stream_cfg.fifo_buffer = stream_fifo_buffer;
    stream_cfg.fifo_buffer_length = fifo_buffer_length;
    stream_cfg.watermark = dma_buffer_length / 2U;

    result = rt_adc_stream_start_frame_aligned_fifo(device, channels, &stream_cfg);
    if (result != RT_EOK)
    {
        rt_free(buffer);
        return result;
    }
    stream_device = device;

    result = RT_EOK;
    read_times = 0U;
    full_count = 0U;
    partial_count = 0U;
    timeout_count = 0U;
    error_count = 0U;
    total_samples = 0U;
    begin_tick = rt_tick_get();
    timeout_tick = rt_tick_from_millisecond(timeout_ms);

    while (rt_tick_get_delta(begin_tick) < timeout_tick)
    {
        rt_ssize_t read_count;

        read_count = rt_adc_stream_read(device, buffer, sample_count, RT_ADC_MSH_FIFO_TEST_READ_TIMEOUT_MS);
        read_times++;
        if (read_count < 0)
        {
            if (read_count == -RT_ETIMEOUT)
            {
                timeout_count++;
                continue;
            }

            result = (rt_err_t)read_count;
            error_count++;
            rt_kprintf("stream fifo test failed at %u: %d\n", (unsigned int)read_times, (int)read_count);
            break;
        }

        total_samples += (rt_size_t)read_count;
        if ((rt_size_t)read_count == sample_count)
        {
            full_count++;
        }
        else
        {
            partial_count++;
        }
    }

    end_tick = rt_tick_get();
    stop_result = rt_adc_stream_stop(device);
    if (stop_result == RT_EOK)
    {
        adc_msh_clear_stream_owner(&stream_device);
    }

    rt_size_t elapsed_tick;
    rt_size_t total_frames;
    rt_size_t read_frames;
    rt_size_t dma_frames;
    rt_size_t fifo_frames;
    rt_size_t frame_rate;
    rt_size_t sample_rate_per_channel;

    elapsed_tick = end_tick - begin_tick;
    total_frames = total_samples / channel_count;
    read_frames = sample_count / channel_count;
    dma_frames = dma_buffer_length / channel_count;
    fifo_frames = fifo_buffer_length / channel_count;

    if (elapsed_tick > 0U)
    {
        frame_rate = (total_frames * RT_TICK_PER_SECOND) / elapsed_tick;
        sample_rate_per_channel = frame_rate;
    }
    else
    {
        frame_rate = 0U;
        sample_rate_per_channel = 0U;
    }

    rt_kprintf("adc fifo_test: %s\n", (error_count == 0U && timeout_count == 0U && partial_count == 0U) ? "PASS" : "FAIL");
    rt_kprintf("  duration        : %d ms\n", (int)timeout_ms);
    rt_kprintf("  channels        : %u\n", (unsigned int)channel_count);
    rt_kprintf("  read block      : %u frames, %u samples\n",
               (unsigned int)read_frames, (unsigned int)sample_count);
    rt_kprintf("  dma buffer      : %u frames, %u samples\n",
               (unsigned int)dma_frames, (unsigned int)dma_buffer_length);
    rt_kprintf("  fifo buffer     : %u frames, %u samples\n",
               (unsigned int)fifo_frames, (unsigned int)fifo_buffer_length);
    rt_kprintf("  read count      : %u\n", (unsigned int)read_times);
    rt_kprintf("  full reads      : %u\n", (unsigned int)full_count);
    rt_kprintf("  partial reads   : %u\n", (unsigned int)partial_count);
    rt_kprintf("  timeouts        : %u\n", (unsigned int)timeout_count);
    rt_kprintf("  errors          : %u\n", (unsigned int)error_count);
    rt_kprintf("  total frames    : %u\n", (unsigned int)total_frames);
    rt_kprintf("  total samples   : %u\n", (unsigned int)total_samples);
    rt_kprintf("  frame rate      : %u frames/s\n", (unsigned int)frame_rate);
    rt_kprintf("  sample rate/ch  : %u samples/s\n", (unsigned int)sample_rate_per_channel);
    rt_kprintf("  elapsed tick    : %u\n", (unsigned int)elapsed_tick);

    rt_free(buffer);
    if (error_count > 0U)
    {
        return result;
    }

    if (timeout_count > 0U)
    {
        return -RT_ETIMEOUT;
    }

    return stop_result;
}
#endif /* defined(RT_ADC_USING_STREAM) && defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO) */

/**
 * @brief Handle the ADC FinSH command.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Command status.
 */
static int adc(int argc, char **argv)
{
    rt_uint32_t values_buf[RT_ADC_MSH_VALUE_BUFFER_SIZE];
    rt_uint32_t *values;
    rt_uint32_t channels;
    rt_uint32_t channel_mask;
    rt_size_t index;
    rt_size_t count;
    rt_ssize_t read_count;
    rt_err_t result;

    if (argc < 2)
    {
        adc_msh_usage();
        return -RT_EINVAL;
    }

    values = values_buf;
    if (!rt_strcmp(argv[1], "probe"))
    {
        rt_device_t new_dev;
        rt_adc_device_t new_device;

        if (argc != 3)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

#ifdef RT_ADC_USING_STREAM
        if (adc_msh_stream_buffer_is_active(stream_device) == RT_TRUE)
        {
            rt_kprintf("adc stream is running, stop it first\n");
            return -RT_EBUSY;
        }
        adc_msh_clear_stream_owner(&stream_device);
#endif /* RT_ADC_USING_STREAM */

        new_dev = rt_device_find(argv[2]);
        if (new_dev == RT_NULL)
        {
            rt_kprintf("adc device %s not found\n", argv[2]);
            return -RT_ERROR;
        }

        if (new_dev->type != RT_Device_Class_ADC)
        {
            rt_kprintf("%s is not an adc device\n", argv[2]);
            return -RT_EINVAL;
        }

        new_device = (rt_adc_device_t)new_dev;
        if (device == new_device)
        {
            rt_kprintf("probe %s: %d\n", argv[2], RT_EOK);
            return RT_EOK;
        }

        result = rt_device_open(new_dev, RT_DEVICE_OFLAG_RDWR);
        if (result != RT_EOK)
        {
            rt_kprintf("probe %s failed: %d\n", argv[2], result);
            return result;
        }

        if (device != RT_NULL)
        {
            rt_err_t close_result;

            close_result = rt_device_close(&device->parent);
            if (close_result != RT_EOK)
            {
                (void)rt_device_close(new_dev);
                rt_kprintf("close previous adc device %s failed: %d\n", device->parent.parent.name, close_result);
                return close_result;
            }
        }

        device = new_device;
        rt_kprintf("probe %s: %d\n", argv[2], result);
        return result;
    }

    if (device == RT_NULL)
    {
        rt_kprintf("no adc device selected\n");
        return -RT_EINVAL;
    }

    if (!rt_strcmp(argv[1], "config"))
    {
        if (argc < 3)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        channels = 0U;
        for (index = 0U; index < (rt_size_t)(argc - 2); index++)
        {
            result = adc_msh_parse_channel_mask(argv[index + 2], &channel_mask);
            if (result != RT_EOK)
            {
                rt_kprintf("invalid adc channel: %s\n", argv[index + 2]);
                return result;
            }
            channels |= channel_mask;
        }

        result = rt_device_control(&device->parent, RT_ADC_CMD_SET_SESSION, &channels);
        if (result == RT_EOK)
        {
            rt_kprintf("config channels=0x%08lx count=%u\n",
                       (unsigned long)channels, (unsigned int)rt_adc_channel_mask_count(channels));
        }
        return result;
    }

    if (!rt_strcmp(argv[1], "read"))
    {
        if (argc > 2)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        if ((device->session_ctrl.configured != RT_TRUE) || (device->session_ctrl.channel_count == 0U))
        {
            rt_kprintf("adc session is not configured, run adc config first\n");
            return -RT_EINVAL;
        }

        count = device->session_ctrl.channel_count;
        if (count > RT_ADC_MSH_VALUE_BUFFER_SIZE)
        {
            rt_kprintf("adc read count too large, max %u samples\n", (unsigned int)RT_ADC_MSH_VALUE_BUFFER_SIZE);
            return -RT_EINVAL;
        }

        read_count = rt_device_read(&device->parent, 0, values, count);
        if (read_count < 0)
        {
            result = (rt_err_t)read_count;
        }
        else if ((rt_size_t)read_count != count)
        {
            result = -RT_ERROR;
        }
        else
        {
            result = RT_EOK;
            for (index = 0U; index < count; index++)
            {
                rt_kprintf("[%u]=%lu\n", (unsigned int)index, (unsigned long)values[index]);
            }
        }
        return result;
    }

    if (!rt_strcmp(argv[1], "voltage"))
    {
        rt_int32_t timeout_ms;

        if (argc != 3)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        if ((device->session_ctrl.configured != RT_TRUE) || (device->session_ctrl.channel_count == 0U))
        {
            rt_kprintf("adc session is not configured, run adc config first\n");
            return -RT_EINVAL;
        }

        timeout_ms = adc_msh_parse_timeout(argv[2]);
        count = device->session_ctrl.channel_count;
        if (count > RT_ADC_MSH_VALUE_BUFFER_SIZE)
        {
            rt_kprintf("adc voltage count too large, max %u samples\n", (unsigned int)RT_ADC_MSH_VALUE_BUFFER_SIZE);
            return -RT_EINVAL;
        }

        result = rt_adc_voltage(device, values, count, timeout_ms);
        if (result == RT_EOK)
        {
            for (index = 0U; index < count; index++)
            {
                rt_kprintf("[%u]=%lu mV\n", (unsigned int)index, (unsigned long)values[index]);
            }
        }
        else if (result == -RT_EINVAL)
        {
            rt_kprintf("adc voltage failed, check adc config and VREF channel/default_vref\n");
        }

        return result;
    }

    if (!rt_strcmp(argv[1], "seq"))
    {
        struct rt_adc_sequence_cfg sequence_cfg;
        rt_size_t sequence_read_count;

        if (argc < 4)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        channels = 0U;
        for (index = 0U; index < (rt_size_t)(argc - 3); index++)
        {
            result = adc_msh_parse_channel_mask(argv[index + 3], &channel_mask);
            if (result != RT_EOK)
            {
                rt_kprintf("invalid adc channel: %s\n", argv[index + 3]);
                return result;
            }
            channels |= channel_mask;
        }

        count = rt_adc_channel_mask_count(channels);
        if (count > RT_ADC_MSH_VALUE_BUFFER_SIZE)
        {
            rt_kprintf("adc seq count too large, max %u samples\n", (unsigned int)RT_ADC_MSH_VALUE_BUFFER_SIZE);
            return -RT_EINVAL;
        }

        rt_memset(&sequence_cfg, 0, sizeof(sequence_cfg));
        sequence_cfg.buffer = values;
        sequence_cfg.buffer_length = count;
        sequence_cfg.timeout_ms = adc_msh_parse_timeout(argv[2]);

        result = rt_adc_read_sequence(device, channels, &sequence_cfg, &sequence_read_count);
        if (result != RT_EOK)
        {
            return result;
        }

        for (index = 0U; index < sequence_read_count; index++)
        {
            rt_kprintf("[%u]=%lu\n", (unsigned int)index, (unsigned long)values[index]);
        }

        return RT_EOK;
    }

#if defined(RT_ADC_USING_TRIGGER)
    if (!rt_strcmp(argv[1], "trigger"))
    {
        return adc_msh_trigger(device, argc - 2, &argv[2]);
    }
#endif /* defined(RT_ADC_USING_TRIGGER) */

    if (!rt_strcmp(argv[1], "close"))
    {
        rt_err_t close_result;

        if (argc > 2)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        close_result = rt_device_close(&device->parent);
        if (close_result != RT_EOK)
        {
            rt_kprintf("close adc device %s failed: %d\n", device->parent.parent.name, close_result);
            return close_result;
        }

        rt_kprintf("close %s: %d\n", device->parent.parent.name, close_result);
        device = RT_NULL;
        return RT_EOK;
    }

#ifdef RT_ADC_USING_STREAM
    if (!rt_strcmp(argv[1], "stream"))
    {
        return adc_msh_stream(device, argc - 2, &argv[2]);
    }

#if defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO)
    if (!rt_strcmp(argv[1], "fifo"))
    {
        return adc_msh_fifo_test(device, argc - 2, &argv[2]);
    }
#endif /* defined(RT_ADC_MSH_USING_FIFO_TEST) && defined(RT_ADC_STREAM_USING_FIFO) */
#endif /* RT_ADC_USING_STREAM */

    result = rt_adc_msh_special(device, argc - 1, &argv[1]);
    if (result != -RT_ENOSYS)
    {
        return result;
    }

    adc_msh_usage();
    return -RT_EINVAL;
}
MSH_CMD_EXPORT(adc, adc v2 command);
#endif /* defined(RT_USING_ADC_V2) && defined(RT_USING_FINSH) && defined(RT_ADC_V2_USING_MSH) */
