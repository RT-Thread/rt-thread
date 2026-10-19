/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_AUDIO) && defined(RT_AUDIO_SPACEMIT) && defined(RT_USING_FINSH)
#include <finsh.h>
#include <stdlib.h>

#define AUDIO_TEST_RATE             48000U
#define AUDIO_TEST_CHANNELS         2U
#define AUDIO_TEST_BITS             16U
#define AUDIO_TEST_BUFFER_SIZE      4096U
#define AUDIO_TEST_DEFAULT_SECONDS  2U
#define AUDIO_TEST_MAX_SECONDS      30U

static const rt_int16_t audio_test_sine[] =
{
       0,  2139,  4240,  6269,  8192,  9974, 11585, 12998,
   14189, 15136, 15825, 16244, 16384, 16244, 15825, 15136,
   14189, 12998, 11585,  9974,  8192,  6269,  4240,  2139,
       0, -2139, -4240, -6269, -8192, -9974,-11585,-12998,
  -14189,-15136,-15825,-16244,-16384,-16244,-15825,-15136,
  -14189,-12998,-11585, -9974, -8192, -6269, -4240, -2139,
};

static int audio_test(int argc, char **argv)
{
    int ret = -RT_ERROR;
    rt_uint32_t phase = 0;
    rt_uint32_t seconds = AUDIO_TEST_DEFAULT_SECONDS;
    rt_size_t remaining;
    rt_device_t device;
    rt_int16_t *buffer;
    const char *name = "snd-es8326";
    struct rt_audio_caps caps = { 0 };

    if (argc > 1)
    {
        name = argv[1];
    }
    if (argc > 2)
    {
        seconds = strtoul(argv[2], RT_NULL, 0);
        if (!seconds || seconds > AUDIO_TEST_MAX_SECONDS)
        {
            rt_kprintf("seconds must be 1..%u\n", AUDIO_TEST_MAX_SECONDS);
            return -RT_EINVAL;
        }
    }

    device = rt_device_find(name);
    if (!device)
    {
        rt_kprintf("audio device %s not found\n", name);
        return -RT_ENOSYS;
    }

    buffer = rt_malloc(AUDIO_TEST_BUFFER_SIZE);
    if (!buffer)
    {
        return -RT_ENOMEM;
    }

    if ((ret = rt_device_open(device, RT_DEVICE_OFLAG_WRONLY)))
    {
        rt_kprintf("open %s failed: %s\n", name, rt_strerror(ret));
        goto _free;
    }

    caps.main_type = AUDIO_TYPE_OUTPUT;
    caps.sub_type = AUDIO_DSP_PARAM;
    caps.udata.config.samplerate = AUDIO_TEST_RATE;
    caps.udata.config.channels = AUDIO_TEST_CHANNELS;
    caps.udata.config.samplebits = AUDIO_TEST_BITS;
    if ((ret = rt_device_control(device, AUDIO_CTL_CONFIGURE, &caps)))
    {
        rt_kprintf("configure %s failed: %s\n", name, rt_strerror(ret));
        goto _close;
    }

    caps.main_type = AUDIO_TYPE_MIXER;
    caps.sub_type = AUDIO_MIXER_VOLUME;
    caps.udata.value = 65;
    rt_device_control(device, AUDIO_CTL_CONFIGURE, &caps);

    remaining = (rt_size_t)seconds * AUDIO_TEST_RATE *
            AUDIO_TEST_CHANNELS * sizeof(rt_int16_t);
    rt_kprintf("playing 1 kHz tone on %s for %u second(s)\n", name, seconds);

    while (remaining)
    {
        rt_size_t size = rt_min_t(rt_size_t, remaining, AUDIO_TEST_BUFFER_SIZE);
        rt_size_t samples = size / sizeof(*buffer);

        for (rt_size_t i = 0; i < samples; i += 2)
        {
            rt_int16_t sample = audio_test_sine[phase];

            buffer[i] = sample;
            buffer[i + 1] = sample;
            phase = (phase + 1) % RT_ARRAY_SIZE(audio_test_sine);
        }

        if (rt_device_write(device, 0, buffer, size) != size)
        {
            rt_kprintf("write %s failed\n", name);
            ret = -RT_EIO;
            goto _close;
        }
        remaining -= size;
    }

    ret = RT_EOK;
    rt_kprintf("audio_test: queued playback data, closing device\n");

_close:
    rt_device_close(device);
    rt_kprintf("audio_test: device closed\n");
_free:
    rt_free(buffer);
    return ret;
}
MSH_CMD_EXPORT(audio_test, play a 1 kHz tone: audio_test [device] [seconds]);
#endif /* RT_USING_AUDIO && RT_AUDIO_SPACEMIT && RT_USING_FINSH */
