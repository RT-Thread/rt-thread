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

static rt_adc_device_t device = RT_NULL;

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
        for (index = 0; index < (rt_size_t)(argc - 2); index++)
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
    else if (!rt_strcmp(argv[1], "read"))
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
            for (index = 0; index < count; index++)
            {
                rt_kprintf("[%u]=%lu\n", (unsigned int)index, (unsigned long)values[index]);
            }
        }
        return result;
    }
    else if (!rt_strcmp(argv[1], "voltage"))
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
    else if (!rt_strcmp(argv[1], "seq"))
    {
        struct rt_adc_sequence_cfg sequence_cfg;
        rt_size_t sequence_read_count;

        if (argc < 4)
        {
            adc_msh_usage();
            return -RT_EINVAL;
        }

        channels = 0U;
        for (index = 0; index < (rt_size_t)(argc - 3); index++)
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

        for (index = 0; index < sequence_read_count; index++)
        {
            rt_kprintf("[%u]=%lu\n", (unsigned int)index, (unsigned long)values[index]);
        }

        return RT_EOK;
    }
    else if (!rt_strcmp(argv[1], "close"))
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
