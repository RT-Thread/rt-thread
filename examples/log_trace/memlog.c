#include <rtthread.h>
#include <rtdevice.h>
#include <log_trace.h>

#define PIPE_SZ    2048
#define PIPE_NAME  "lgpipe"

static rt_uint8_t pipebuf[PIPE_SZ];
static struct rt_pipe_device pipedev;

static rt_uint8_t outbuf[1024];
void memlog_flush(void)
{
    rt_size_t remainsz, readsz;
    rt_device_t console;

    console = rt_console_get_device();

    if (!console)
        return;

    rt_device_control((rt_device_t)&pipedev, PIPE_CTRL_GET_SPACE, &remainsz);
    if (remainsz == 0)
    {
        rt_kprintf("logtrace pipe "PIPE_NAME" is full, some log may lost\n");
    }

    readsz = rt_device_read((rt_device_t)&pipedev, 0, outbuf, sizeof(outbuf));
    if (readsz)
        rt_device_write(console, 0, outbuf, readsz);
}

void memlog_init(void)
{
    rt_err_t res;

    /* make sure the RT_PIPE_FLAG_BLOCK_RD is not set. The Idle should not be
     * blocked. RT_PIPE_FLAG_FORCE_WR will let the pipe discard some old data
     * when pipe is full. */
    res = rt_pipe_init(&pipedev, PIPE_NAME, RT_PIPE_FLAG_FORCE_WR,
                       pipebuf, sizeof(pipebuf));
    if (res != RT_EOK)
    {
        rt_kprintf("init pipe device failed: %d\n", res);
        return;
    }

    log_trace_set_device(PIPE_NAME);

    rt_thread_idle_sethook(memlog_flush);
}

