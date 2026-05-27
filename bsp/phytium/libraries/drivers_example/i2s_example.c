#include <rtthread.h>
#include <rtdevice.h>

#define SOUND_DEVICE_NAME    "I2S0"

#define RECORD_SAMPLERATE    16000
#define RECORD_CHANNEL       1
#define RECORD_SAMPLEBITS    16

#define RECORD_BUF_SZ        640     /* 20ms:
                                      * 16000 * 1 * 2 * 20 / 1000
                                      */

static rt_device_t mic_dev = RT_NULL;

static int mic_test(int argc, char **argv)
{
    struct rt_audio_caps caps;
    rt_int16_t *buffer;
    int length;
    int i;

    buffer = rt_malloc(RECORD_BUF_SZ);
    if (buffer == RT_NULL)
    {
        rt_kprintf("malloc failed\n");
        return -1;
    }

    /* 查找录音设备 */
    mic_dev = rt_device_find(SOUND_DEVICE_NAME);
    if (mic_dev == RT_NULL)
    {
        rt_kprintf("can't find %s\n", SOUND_DEVICE_NAME);
        rt_free(buffer);
        return -1;
    }

    rt_kprintf("find device: %s\n", SOUND_DEVICE_NAME);

    /* 打开录音设备 */
    if (rt_device_open(mic_dev, RT_DEVICE_OFLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open device failed\n");
        rt_free(buffer);
        return -1;
    }

    rt_kprintf("open success\n");

    /* 配置录音参数 */
    caps.main_type               = AUDIO_TYPE_INPUT;
    caps.sub_type                = AUDIO_DSP_PARAM;
    caps.udata.config.samplerate = RECORD_SAMPLERATE;
    caps.udata.config.channels   = RECORD_CHANNEL;
    caps.udata.config.samplebits = RECORD_SAMPLEBITS;

    if (rt_device_control(mic_dev, AUDIO_CTL_CONFIGURE, &caps) != RT_EOK)
    {
        rt_kprintf("configure failed\n");
        goto __exit;
    }

    rt_kprintf("record start ...\n");

    while (1)
    {
        /* 读取录音数据 */
        length = rt_device_read(mic_dev, 0, buffer, RECORD_BUF_SZ);

        if (length > 0)
        {
            rt_kprintf("read %d bytes: ", length);

            /* 打印前 8 个采样点 */
            for (i = 0; i < 8; i++)
            {
                rt_kprintf("%d ", buffer[i]);
            }

            rt_kprintf("\n");
        }
        else
        {
            rt_kprintf("read no data\n");
        }

        rt_thread_mdelay(20);
    }

__exit:

    rt_device_close(mic_dev);
    rt_free(buffer);

    return 0;
}

MSH_CMD_EXPORT(mic_test, mic record test);