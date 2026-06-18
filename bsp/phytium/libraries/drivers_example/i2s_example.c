#include <rtconfig.h>
#ifdef BSP_USING_I2S_LAYER
#include <rtthread.h>
#include <rtdevice.h>

#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)
    #define AUDIO_DEVICE_NAME    "I2S0"
#endif
#if defined(PD2408_TEST_B_BOARD)
    #define AUDIO_DEVICE_NAME    "I2S0_MSG"
#endif

#define AUDIO_SAMPLERATE     16000
#define AUDIO_CHANNELS       2
#define AUDIO_SAMPLEBITS     16
#define RECORD_SECONDS       5
#define RECORD_TOTAL_SIZE \
    (AUDIO_SAMPLERATE * AUDIO_CHANNELS * \
     (AUDIO_SAMPLEBITS / 8) * RECORD_SECONDS)

/* 每次读20ms */
#define AUDIO_BUF_SIZE       RT_AUDIO_REPLAY_MP_BLOCK_SIZE

static rt_device_t audio_dev = RT_NULL;

static int i2s_record_play_test(int argc, char **argv)
{
    struct rt_audio_caps caps;

    rt_uint8_t *record_buf = RT_NULL;
    rt_uint8_t *tmp_buf = RT_NULL;

    int read_len;
    int write_len;

    int offset = 0;

    rt_kprintf("\n");
    rt_kprintf("=================================\n");
    rt_kprintf(" I2S Record And Playback Test\n");
    rt_kprintf("=================================\n");

    /******************************************************
     * 分配录音总buffer
     ******************************************************/
    record_buf = rt_malloc(RECORD_TOTAL_SIZE);

    if (record_buf == RT_NULL)
    {
        rt_kprintf("malloc record_buf failed\n");
        return -1;
    }

    rt_memset(record_buf, 0, RECORD_TOTAL_SIZE);

    /******************************************************
     * 分配临时buffer
     ******************************************************/
    tmp_buf = rt_malloc(AUDIO_BUF_SIZE);

    if (tmp_buf == RT_NULL)
    {
        rt_kprintf("malloc tmp_buf failed\n");

        rt_free(record_buf);

        return -1;
    }

    /******************************************************
     * 查找设备
     ******************************************************/
    audio_dev = rt_device_find(AUDIO_DEVICE_NAME);

    if (audio_dev == RT_NULL)
    {
        rt_kprintf("can't find %s\n", AUDIO_DEVICE_NAME);

        goto __exit;
    }

    rt_kprintf("find device: %s\n", AUDIO_DEVICE_NAME);

    /******************************************************
     * 打开设备
     ******************************************************/
    if (rt_device_open(audio_dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("open device failed\n");

        goto __exit;
    }

    rt_kprintf("open success\n");

    /******************************************************
     * 配置输入
     ******************************************************/
    caps.main_type               = AUDIO_TYPE_INPUT;
    caps.sub_type                = AUDIO_DSP_PARAM;

    caps.udata.config.samplerate = AUDIO_SAMPLERATE;
    caps.udata.config.channels   = AUDIO_CHANNELS;
    caps.udata.config.samplebits = AUDIO_SAMPLEBITS;

    if (rt_device_control(audio_dev,
                          AUDIO_CTL_CONFIGURE,
                          &caps) != RT_EOK)
    {
        rt_kprintf("input configure failed\n");

        goto __close;
    }

    /******************************************************
     * 配置输出
     ******************************************************/
    caps.main_type               = AUDIO_TYPE_OUTPUT;
    caps.sub_type                = AUDIO_DSP_PARAM;

    caps.udata.config.samplerate = AUDIO_SAMPLERATE;
    caps.udata.config.channels   = AUDIO_CHANNELS;
    caps.udata.config.samplebits = AUDIO_SAMPLEBITS;

    if (rt_device_control(audio_dev,
                          AUDIO_CTL_CONFIGURE,
                          &caps) != RT_EOK)
    {
        rt_kprintf("output configure failed\n");

        goto __close;
    }

    /******************************************************
     * 开始录音
     ******************************************************/
    rt_kprintf("\n");
    rt_kprintf("Start recording %d seconds...\n",
               RECORD_SECONDS);

    offset = 0;

    while (offset < RECORD_TOTAL_SIZE)
    {
        read_len = rt_device_read(audio_dev,
                                  0,
                                  tmp_buf,
                                  AUDIO_BUF_SIZE);

        if (read_len > 0)
        {
            rt_memcpy(record_buf + offset,
                      tmp_buf,
                      read_len);

            offset += read_len;
        }
        else
        {
            rt_thread_mdelay(10);
        }

    }

    rt_kprintf("\n");
    rt_kprintf("Record finished.\n");

    /******************************************************
     * 等待1秒
     ******************************************************/
    rt_thread_mdelay(1000);

    /******************************************************
     * 开始播放
     ******************************************************/
    rt_kprintf("Start playback...\n");

    offset = 0;

    while (offset < RECORD_TOTAL_SIZE)
    {

        write_len = AUDIO_BUF_SIZE;

        if ((offset + write_len) > RECORD_TOTAL_SIZE)
        {
            write_len = RECORD_TOTAL_SIZE - offset;
        }

        write_len = rt_device_write(audio_dev,
                                    0,
                                    record_buf + offset,
                                    write_len);

        if (write_len > 0)
        {
            offset += write_len;
        }
    }

    rt_kprintf("\n");
    rt_kprintf("Playback finished.\n");

__close:

    rt_device_close(audio_dev);

__exit:

    if (record_buf)
    {
        rt_free(record_buf);
    }

    if (tmp_buf)
    {
        rt_free(tmp_buf);
    }

    return 0;
}

MSH_CMD_EXPORT(i2s_record_play_test,
               i2s record 5s and playback 5s test);
#endif