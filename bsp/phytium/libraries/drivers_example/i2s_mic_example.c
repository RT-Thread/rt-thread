/* pcm_record.c */
#include "rtconfig.h"
#if defined(BSP_USING_I2S)||defined(BSP_USING_SDIF)
#include <rtthread.h>
#include <rtdevice.h>
#include <dfs_posix.h>

#define RECORD_TIME_MS      5000
#define RT_I2S_SAMPLERATE   8000
#define RECORD_CHANNEL      2
#define RECORD_CHUNK_SZ     ((RT_I2S_SAMPLERATE * RECORD_CHANNEL * 2) * 20 / 1000)

#define SOUND_DEVICE_NAME    "I2S0"      /* Audio 设备名称 */
static rt_device_t mic_dev;              /* Audio 设备句柄 */

int pcm_record()
{
    int fd = -1;
    uint8_t *buffer = NULL;
    int length, total_length = 0;

    fd = open("file.pcm", O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        rt_kprintf("open file for recording failed!\n");
        return -1;
    }
    rt_kprintf("1\n");
    buffer = rt_malloc(RECORD_CHUNK_SZ);
    if (buffer == RT_NULL)
        goto __exit;
    rt_kprintf("2\n");
    mic_dev = rt_device_find(SOUND_DEVICE_NAME);
    if (mic_dev == RT_NULL)
        goto __exit;
    rt_kprintf("3\n");
    rt_device_open(mic_dev, RT_DEVICE_OFLAG_RDONLY);
    rt_kprintf("4\n");
    while (1)
    {
        rt_kprintf("6\n");
        length = rt_device_read(mic_dev, 0, buffer, RECORD_CHUNK_SZ);
        rt_kprintf("7\n");
        if (length)
        {
            write(fd, buffer, length);
            total_length += length;
        }

        if ((total_length / RECORD_CHUNK_SZ) >  (RECORD_TIME_MS / 20))
            break;
    }

    close(fd);

    rt_device_close(mic_dev);

__exit:
    if (fd >= 0)
        close(fd);

    if (buffer)
        rt_free(buffer);

    return 0;
}
MSH_CMD_EXPORT(pcm_record, record voice to a pcm file);  // 修改命令描述
#endif